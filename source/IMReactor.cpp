#include <pthread.h>
#include <cstring>


#include "IMReactor.h"
#include "UtilLog.h"


using namespace IM;


IMReactor* IMReactor::_thisReactor = nullptr;



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
	if(IP == NULL)
		sockUtil::setNetServerAddr(&addr, port);
	else 
		sockUtil::setNetServerAddr(&addr, IP, port);
	sock_listen = sockUtil::listenToAddr(&addr, 10);
	if(sock_listen == -1) 
	{
		Util::Log::log(Util::Log::ERROR, "server sock_listen listen to Address error");
		return ;
	}
	event_count = 1;
	epoll_event event;
	event.data.fd = sock_listen;
	event.events = EPOLLIN;
	epoll_root = epoll_create(10);
	if(-1 == epoll_ctl(epoll_root, EPOLL_CTL_ADD, sock_listen,  &event) )
	{
	
		event_count = 0;
		Util::Log::log(Util::Log::ERROR, "epoll ctl error");
		return ;
	}
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
	while(true)
	{
		{std::lock_guard<std::mutex> lock(que_mutex);
			while(!que.empty()) {
				auto& eve = que.front();
				epoll_event event;
				event.events = eve.getEvent();
				event.data.fd = eve.getScoket();
				epoll_ctl(epoll_root, eve.getOpt(), eve.getScoket(), &event);
				event_count++;
				que.pop();
			}
		}

		int n = ::epoll_wait(epoll_root, &*events.begin(), static_cast<int>(events.size()), 0);

		//扩容
		if(n > 0 && events.size() == static_cast<size_t>(n))
			events.resize(n * 2);

		for(int i=0; i<n; ++i) {
			auto& cur = events[i];
			if(cur.data.fd == sock_listen) {
				//新连接
				std::cout << "新的连接" << std::endl;
				//处理新连接
				std::shared_ptr<Task> task = std::make_shared<NewConnectTask> (sockToConn[sock_listen]); 
				//添加到一个线程任务中
				auto taskThread = getIdelThread();
				taskThread->addTask(task);

			} else {
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
					std::shared_ptr<Task> task = std::make_shared<Task> (connecter);
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
	Util::Log::log(Util::Log::INFO, "IMTask线程启动成功！");
	while(true)
	{
		auto task = taskTread->getTask();
		task->doit();
	}

}/*}}}*/


void Task::doit() {

}

void ReadableTask::doit() {

}

void WriteableTask::doit() {
	/* TODO:  <07-04-19, yourname> */
	/* 做可写事件处理
	 * 将缓冲区的数据写入套接字内
	 */

}


void NewConnectTask::doit() {
	/* TODO:  <20-04-19, sky> 
	 *
	 * 接受一个或者多个新的连接
	 * 为每个新的连接创建一个connecter， 并添加到sockToConn中
	 * 想监听队列中添加一个需要监听的事件
	 * */



}


