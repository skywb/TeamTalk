#include <pthread.h>
#include <cstring>
#include <fcntl.h>
#include <functional>


#include "reactor/IMReactor.h"
#include "util/Log.h"


using namespace IM;


IMReactor* IMReactor::_thisReactor = nullptr;


void ThreadPool::callBack_threadPool(ThreadPool* p) {
	while(true) {
		auto task = p->getTask();
		if(task == nullptr) break;
		task->doit();
	}
}


ThreadPool::ThreadPool(size_t num) : 
	m_mutex(), m_cond(), thread_num(num), 
	m_started(false) {
}



ThreadPool::~ThreadPool() {
	if(m_started) {
		stop();
	}
}


void ThreadPool::start() {
	assert(threads.empty());
	m_started = true;
	for(size_t i=0; i<thread_num; ++i) {
		threads.push_back(
				std::make_shared<std::thread> (
					std::bind(callBack_threadPool, this)));
	}
}


void ThreadPool::stop() {
	{ std::unique_lock<std::mutex> lock(m_mutex);
		m_started = false;
		//唤醒所有等待的线程， 线程自动退出, 等待回收
		m_cond.notify_all();
	}

	for(auto& i : threads) {
		i->join();
		i = nullptr;
	}
	threads.clear();
}

bool ThreadPool::addTask(std::shared_ptr<Task> task) {
	std::lock_guard<std::mutex> lock(m_mutex);
	if(m_started == false) return false;
	taskQue.push(task);
	m_cond.notify_one();
	return true;
}

std::shared_ptr<Task> ThreadPool::getTask() {
	std::unique_lock<std::mutex> lock(m_mutex);

	while(taskQue.empty() || m_started ) {
		m_cond.wait(lock);
	}

	Log::log(Log::INFO, "thread getTask");
	if(m_started && !taskQue.empty()) {
		auto res = taskQue.front();
		taskQue.pop();
		return res;
	}
	return nullptr;
}

bool ThreadPool::addThreadsToPool(size_t num) {
	/* TODO:  <14-05-19, yourname> */
	(void)num;	
	return false;
}

bool ThreadPool::reducedThreadsFromPool(size_t num) {
	/* TODO:  <14-05-19, yourname> */
	(void)num;	
	return false;
}


TaskThread::TaskThread () {/*{{{*/
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&cond, NULL);
}/*}}}*/

void TaskThread::join(callBack callBack_fun, void* arg) {

	::pthread_create(&pid, NULL, callBack_fun, arg);
}

TaskThread::~TaskThread () {
}


void TaskThread::addTask(std::shared_ptr<Task> task) {

	pthread_mutex_lock(&_mutex);
	Tasks.push(task);
	::pthread_cond_signal(&cond);
	pthread_mutex_unlock(&_mutex);
}





std::shared_ptr<Task> TaskThread::getTask() {/*{{{*/
	//std::lock_guard<pthread_mutex_t> lock(_mutex);
	pthread_mutex_lock(&_mutex);
	pthread_cond_wait(&cond, &_mutex);
	auto p = Tasks.front();
	Tasks.pop();
	pthread_mutex_unlock(&_mutex);
	return p;
}/*}}}*/



IMReactor::IMReactor (const char *IP, uint16_t port) {/*{{{*/
	if(_thisReactor != nullptr) return ;

	idelTaskNum = 0;
	idelTaskIndex = 0;

	//启动十个任务线程
	for(int i=0; i<10; ++i)
	{
		TaskThread* p = new TaskThread();
		threads.push_back(std::shared_ptr<TaskThread> (p));
		threads[i]->join(IMTaskCallBack, (void*)p);
	}

	sockaddr_in addr;
	if(IP == NULL) {
		if(false == sockUtil::setNetServerAddr(&addr, port) ) {
			Log::log(Log::ERROR, "set server Address error");
		}
	}
	else 
	{
		if(false == sockUtil::setNetServerAddr(&addr, IP, port) ) {
			Log::log(Log::ERROR, "set server Address error");
		}
	}
	sock_listen = sockUtil::listenToAddr(&addr, 10);
	if(sock_listen == -1) 
	{
		Log::log(Log::ERROR, "server sock_listen listen to Address error");
		return ;
	}
	//创建监听红黑树
	epoll_root = epoll_create(10);

	//设置连接监听事件
	event_count = 1;
	epoll_event event;
	event.data.fd = sock_listen;
	event.events = EPOLLIN | EPOLLET;
	sockUtil::setNoBlock(sock_listen);
	if(-1 == epoll_ctl(epoll_root, EPOLL_CTL_ADD, sock_listen,  &event) )
	{
		event_count = 0;
		Log::log(Log::ERROR, "epoll ctl error");
		return ;
	}
	Log::log(Log::DEBUG, "epoll create");
}/*}}}*/

IMReactor::~IMReactor() {
	//fixit 没有关闭其他的文件描述符
	close(sock_listen);
}

IMReactor* IMReactor::getInstances() {
	return _thisReactor;
}


IMReactor* IMReactor::IMReactorInit(const char* IP, uint16_t port) {
	if(_thisReactor == nullptr) 
		_thisReactor = new IMReactor(IP, port);
	return _thisReactor;
}



void IMReactor::loop() {/*{{{*/
	Log::log(Log::DEBUG, "begin listen");
	const int MAX_EVENTS = 100000;
	epoll_event eventss[MAX_EVENTS];
	while(true)
	{
		//std::cout << "add event" << std::endl;
		{std::lock_guard<std::mutex> lock(que_mutex);
			while(!que.empty()) {
				auto& eve = que.front();
				epoll_event event;
				//设置ET模式
				event.events = eve.getEvent() | EPOLLET;
				event.data.fd = eve.getScoket();
				epoll_ctl(epoll_root, eve.getOpt(), eve.getScoket(), &event);
				if(eve.getOpt() == EPOLL_CTL_ADD)
					sockToConn[eve.getScoket()] = std::make_shared<Connecter> (eve.getScoket());
				else if(eve.getOpt() == EPOLL_CTL_DEL) 
					sockToConn[eve.getScoket()].reset();

				event_count++;
				que.pop();
			}
		}
		
		//int n = ::epoll_wait(epoll_root, &*events.begin(), static_cast<int>(events.size()), -1);
		int n = ::epoll_wait(epoll_root, eventss, MAX_EVENTS, -1);
		//std::cout << "epoll n " << n << std::endl;
		if(n == -1)
			std::cout << strerror(errno) << " : " << __FILE__ << " : " << __LINE__ << std::endl;

		//扩容
		//if(n > 0 && events.size() == static_cast<size_t>(n))
		//	events.resize(n * 2);

		//std::cout << n << std::endl;
		for(int i=0; i<n; ++i) {
			auto& cur = eventss[i];
			if(cur.data.fd == sock_listen) {
				//新连接
				//std::cout << "新的连接" << std::endl;
				//处理新连接
				//std::shared_ptr<Task> task = std::make_shared<NewConnectTask> (sockToConn[sock_listen]); 
				////添加到一个线程任务中
				//auto taskThread = getIdelThread();
				//taskThread->addTask(task);

				
				/* FIXIT: 
				 * 此处代码应该拿到线程中去做
				 * <24-04-19, sky> */
				while(true) {
					int nfd = sockUtil::acceptNewConnect(sock_listen);	
					sockUtil::setNoBlock(nfd);
					if(nfd == -1) break;
					//std::cout << "new sockfd = " << nfd << std::endl;
					IMReactor::optEventListen(Event(EPOLL_CTL_ADD, EPOLLIN, nfd));
				}

			} else {
				//std::cout << "new msg" << std::endl;
				if(cur.events == EPOLLIN) {
					//可读 
					/*
					 * 根据套接字获取connecter
					 * 创建Task
					 * 分配工作线程
					 */
					auto connecter = getConnecter(cur.data.fd);
					std::shared_ptr<Task> task = std::make_shared<ReadableTask> (connecter);
					auto taskThread = getIdelThread();
					taskThread->addTask(task);
					
				} else {
					//可写
					/*
					 * 根据套接字获取connecter
					 * 创建新的事件
					 * 创建WriteableTask
					 * 将task分配给工作线程
					 */
					auto connecter = getConnecter(cur.data.fd);
					std::shared_ptr<Task> task = std::make_shared<WriteableTask> (connecter);
					auto taskThread = getIdelThread();
					taskThread->addTask(task);
				}

			}

		}


	}

}/*}}}*/


void IMReactor::optEventListen(Event event) {/*{{{*/
	IMReactor* reactor = getInstances();
	reactor->eventAdd(event);
}/*}}}*/

void IMReactor::eventAdd(Event event) {
	std::lock_guard<std::mutex> lock(que_mutex);
	que.push(event);
}

std::shared_ptr<TaskThread> IMReactor::getIdelThread() {
	if(idelTaskNum > 0) {
		--idelTaskNum;
		return threads[idelTaskIndex];
	} else {

		/* TODO: 
		 *
		 * 负载均衡， 临时使用下一个线程
		 * <20-04-19, sky> */

		idelTaskNum = 10;
		++idelTaskIndex;
		idelTaskIndex %= threads.size();
		return threads[idelTaskIndex];
	}
	
}



void* IM::IMTaskCallBack (void *arg) { /*{{{*/

	if(arg == nullptr) return nullptr;
	TaskThread* taskTread = (TaskThread*)arg;
	Log::log(Log::INFO, "IMTask线程启动成功！");
	while(true)
	{
		auto task = taskTread->getTask();
		task->doit();
	}

}/*}}}*/

