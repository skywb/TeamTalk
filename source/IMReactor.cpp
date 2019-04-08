#include <pthread.h>


#include "IMReactor.h"
#include "UtilLog.h"


using namespace IM;


IMReactor* IMReactor::_thisReactor = nullptr;



TaskThread::TaskThread (callBack callBack_fun) {
	pthread_cond_init(&cond, NULL);
	::pthread_create(&pid, NULL, callBack_fun, (void*)this);
}

TaskThread::~TaskThread () {
}

std::shared_ptr<Task> TaskThread::getTask() {
	//std::lock_guard<pthread_mutex_t> lock(_mutex);
	pthread_mutex_lock(&_mutex);
	pthread_cond_wait(&cond, &_mutex);
	auto p = Tasks.front();
	Tasks.pop();
	pthread_mutex_unlock(&_mutex);
	return p;
}



IMReactor::IMReactor (char *IP, uint16_t port) {
	if(_thisReactor != nullptr) return ;


	//启动十个任务线程
	for(int i=0; i<10; ++i)
		threads.push_back(TaskThread(IMTaskCallBack));

	sockaddr_in addr;
	if(IP == NULL)
		sockUtil::setNetServerAddr(&addr, port);
	else 
		sockUtil::setNetServerAddr(&addr, IP, port);
	sock_listen = sockUtil::listenToAddr(&addr, 10);
	if(sock_listen == -1) 
	{
		//log(error);
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
}

IMReactor::~IMReactor() {
	//fixit 没有关闭其他的文件描述符
	close(sock_listen);
}

IMReactor* IMReactor::getInstances() {
	return _thisReactor;
}


IMReactor* IMReactor::IMReactorInit(char* IP, uint16_t port) {
	if(_thisReactor == nullptr) 
		IMReactor(IP, port);
	return _thisReactor;
}


void IMReactor::loop() {
	/* TODO: 使用epoll监听事件， 分配给线程任务 */
	while(true)
	{
		{std::lock_guard<std::mutex> lock(que_mutex);
			while(!que.empty()) {
				auto& eve = que.front();
				epoll_event event;
				event.events = eve.getEvent();
				event.data.fd = eve.getScoket();
				epoll_ctl(epoll_root, EPOLL_CTL_ADD, eve.getScoket(), &event);
				event_count++;
				que.pop();
			}
		}

		int n = ::epoll_wait(epoll_root, &*events.begin(), static_cast<int>(events.size()), 0);

		if(n > 0 && events.size() == static_cast<size_t>(n))
			events.resize(n * 2);
		for(int i=0; i<n; ++i) {
			auto& cur = events[i];
			if(cur.data.fd == sock_listen) {
				//新连接
				/* TODO:  <07-04-19, yourname> */

			} else {
				if(cur.events == EPOLLIN) {
					//可读 
					/*
					 * 根据套接字获取connecter
					 * 创建Task
					 * 分配工作线程
					 */
					
				} else {
					//可写
					/*
					 * 根据套接字获取connecter
					 * 创建新的事件
					 * 创建WriteableTask
					 * 将task分配给工作线程
					 */

				}

			}

		}


	}

}


void IMReactor::addEventListen(Event event) {
	IMReactor* reactor = getInstances();
	reactor->eventAdd(event);
}

void IMReactor::eventAdd(Event event) {
	std::lock_guard<std::mutex> lock(que_mutex);
	que.push(event);
}




void* IMTaskCallBack (void *arg) {

	if(arg == nullptr) return nullptr;
	TaskThread& taskTread = *((TaskThread*)arg);
	while(true)
	{
		auto task = taskTread.getTask();
		task->doit();
	}

}


void WriteableTask::doit() {
	/* TODO:  <07-04-19, yourname> */
	/* 做可写事件处理
	 * 将缓冲区的数据写入套接字内
	 */

	p_con->send();

}




