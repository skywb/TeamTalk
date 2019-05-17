#ifndef IMREACTOR_H_KZTSCYOX
#define IMREACTOR_H_KZTSCYOX


#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <sys/epoll.h>
#include <sys/types.h>
#include <pthread.h>
#include <condition_variable>

#include <boost/noncopyable.hpp>

#include "reactor/Connecter.h"
#include <reactor/task.h>


namespace IM {

	/*
	 * IM事件
	 */
	class Event
	{/*{{{*/
	public:

		Event (int opt, EPOLL_EVENTS event, int fd) 
			: fd(fd), opt(opt), event(event) { }

		//void setScok(int _fd) { fd = _fd; }

		int getScoket() { return fd; }

		EPOLL_EVENTS getEvent() {
			return event;
		}	

		//获取如何操作epoll
		int getOpt() { return opt; }


		virtual ~Event () {}
	
	protected:
		int fd;
		int opt;
		EPOLL_EVENTS event;
	};/*}}}*/



	class ThreadPool  : public boost::noncopyable
	{
	public:
		ThreadPool (size_t num = 10);
		virtual ~ThreadPool ();

		//开始所有线程, 等待任务
		void start();

		//停止所有线程, 不再接收任务
		void stop();

		//添加一个task， 同时唤醒一个线程(如果有等待线程的话，否则放到等待队列中)
		bool addTask(std::shared_ptr<Task> task);
		//从队列中获取一个task
		std::shared_ptr<Task> getTask();

		//size_t size() { return taskQue.size(); }


		//扩展线程池大小
		bool addThreadsToPool(size_t num);
		//缩减线程池大小
		bool reducedThreadsFromPool(size_t num);
	
	private:
		static void callBack_threadPool(ThreadPool* p);

		//条件变量锁
		std::mutex  m_mutex;
		//task条件变量
		std::condition_variable m_cond;

		//保存所有线程状态
		std::vector<std::shared_ptr<std::thread>> threads;

		size_t thread_num;

		//true表示线程已经运行
		bool m_started;

		//等待队列
		std::queue<std::shared_ptr<Task>> taskQue;

	};

	///*
	// * 任务工作线程， 其中callBack是线程回调函数
	// */
	//class TaskThread
	//{
	//public:
	//	//typedef  epoll_event Event;
	//	typedef void* (*callBack) (void *);
	//	TaskThread ();
	//	virtual ~TaskThread ();

	//	std::shared_ptr<Task> getTask();
	//	void addTask(std::shared_ptr<Task> task);

	//	int getTaskCount() { return Tasks.size(); }
	//	void join(callBack callBack_fun, void* arg);
	//
	//private:
	//	pthread_t pid;
	//	pthread_cond_t cond;
	//	pthread_mutex_t _mutex;
	//	//std::mutex  _mutex;
	//	std::queue<std::shared_ptr<Task>> Tasks;
	//};

	class IMReactor
	{/*{{{*/
	public:
		virtual ~IMReactor ();
	
		static IMReactor* getInstances();
		static IMReactor* IMReactorInit(const char* IP, uint16_t port);
		static void optEventListen (Event event);
		std::shared_ptr<Connecter> getConnecter(int sockfd) {
			return sockToConn[sockfd];	
		}
		void delConnecter(int sockfd) {
			//从mp中删除这个connecter
			sockToConn[sockfd].reset();
		}

		void eventAdd(Event event);

		//std::shared_ptr<TaskThread> getIdelThread();

		void addTask(std::shared_ptr<Task> task);

		void loop();

	private:
		IMReactor (const char* IP, uint16_t port);
		int sock_listen;
		int epoll_root;
		
		//当前空闲进程还能承载的任务数量
		int idelTaskNum;
		int idelTaskIndex;

		size_t event_count;

		void* (*TaskThreadCallBack) (void* arg);

		std::queue<Event> que;
		std::mutex que_mutex;

		//std::vector<epoll_event> events;
		//std::vector<std::shared_ptr<TaskThread>> threads;
		ThreadPool threads;
		std::map<int, std::shared_ptr<Connecter>> sockToConn;

		static IMReactor* _thisReactor;
	};/*}}}*/

	//void* IMTaskCallBack (void* arg);


}

#endif /* end of include guard: IMREACTOR_H_KZTSCYOX */
