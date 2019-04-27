#ifndef IMREACTOR_H_KZTSCYOX
#define IMREACTOR_H_KZTSCYOX


#include <queue>
#include <mutex>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <sys/epoll.h>
#include <sys/types.h>
#include <pthread.h>

#include "Connecter.h"


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


	/*
	 * 任务基类， 每个工作线程获得该基类指针，
	 * 不同的任务都派生自该基类， 实现doit任务处理函数
	 * 在每个工作线程中， 拿到该Task之后调用doit执行任务.
	 */
	class Task {
	public:
		Task(std::shared_ptr<Connecter> connecter_ptr) : 
			p_con(connecter_ptr) { }

		virtual void doit();

		~Task() { }
	protected:
		std::shared_ptr<Connecter> p_con;
	};



	class WriteableTask : public Task
	{
	public:
		WriteableTask (std::shared_ptr<Connecter> connecter_ptr) : 
			Task(connecter_ptr) { }

		virtual ~WriteableTask () { }

		void doit() override ;

	};

	class ReadableTask : public Task
	{
	public:
		ReadableTask (std::shared_ptr<Connecter> connecter_ptr) : 
			Task(connecter_ptr) { }

		virtual ~ReadableTask () { }

		void doit() override ;

	};

	class NewConnectTask : public Task
	{
	public:
		NewConnectTask (std::shared_ptr<Connecter> connecter_ptr) : 
			Task(connecter_ptr) { }

		virtual ~NewConnectTask () { }

		void doit() override ;

	};




	/*
	 * 任务工作线程， 其中callBack是线程回调函数
	 */
	class TaskThread
	{
	public:
		//typedef  epoll_event Event;
		typedef void* (*callBack) (void *);
		TaskThread ();
		virtual ~TaskThread ();

		std::shared_ptr<Task> getTask();
		void addTask(std::shared_ptr<Task> task);

		int getTaskCount() { return Tasks.size(); }
		void join(callBack callBack_fun, void* arg);
	
	private:
		pthread_t pid;
		pthread_cond_t cond;
		pthread_mutex_t _mutex;
		//std::mutex  _mutex;
		std::queue<std::shared_ptr<Task>> Tasks;
	};

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
		void eventAdd(Event event);

		std::shared_ptr<TaskThread> getIdelThread();


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
		std::vector<std::shared_ptr<TaskThread>> threads;
		std::map<int, std::shared_ptr<Connecter>> sockToConn;

		static IMReactor* _thisReactor;
	};/*}}}*/

	void* IMTaskCallBack (void* arg);


}

#endif /* end of include guard: IMREACTOR_H_KZTSCYOX */
