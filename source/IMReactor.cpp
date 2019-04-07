#include "IMReactor.h"
#include <pthread.h>

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
		threads.push_back(TaskThread(TaskThreadCallBack));

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
	epoll_event event;
	event.data.fd = sock_listen;
	event.events = EPOLLIN;
	epoll_root = epoll_create(10);
	if(-1 == epoll_ctl(epoll_root, EPOLL_CTL_ADD, sock_listen,  &event) )
	{
		//log 
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
}



void* IMTaskCallBack (void *arg) {

	TaskThread& taskTread = *((TaskThread*)arg);
	/* TODO: 拆包分配任务 */

}



