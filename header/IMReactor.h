#ifndef IMREACTOR_H_KZTSCYOX
#define IMREACTOR_H_KZTSCYOX


#include <queue>
#include <mutex>
#include <vector>
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
	{
	public:

		enum EVENTS {
			READABLE = 0x10,
			WRITEABLE = 0x20
		};

		Event (EVENTS e) : event(e) { }

		void setScok(int _fd) { fd = _fd; }

		int getScoket() { return fd; }

		virtual EPOLL_EVENTS getEvent() {
			switch (event) {
				case READABLE:
					return EPOLLIN;
				case WRITEABLE:
					return EPOLLOUT;
			}
			return EPOLLIN;
		}	

		virtual ~Event () {}
	
	protected:
		int fd;
		EVENTS event;
	};


	/*
	 * 任务基类， 每个工作线程获得该基类指针，
	 * 不同的任务都派生自该基类， 实现doit任务处理函数
	 * 在每个工作线程中， 拿到该Task之后调用doit执行任务.
	 */
	class Task {
	public:
		Task(Event event, std::shared_ptr<Connecter> connecter_ptr) : 
			m_eve(event), p_con(connecter_ptr) { }

		virtual void doit();

		~Task() { }
	protected:
		Event m_eve;
		std::shared_ptr<Connecter> p_con;
	};



	class WriteableTask : public Task
	{
	public:
		WriteableTask (Event event, std::shared_ptr<Connecter> connecter_ptr) : 
			Task(event, connecter_ptr) { }

		virtual ~WriteableTask () { }


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
		TaskThread (callBack callBack_fun);
		virtual ~TaskThread ();

		std::shared_ptr<Task> getTask();
	
	private:
		pthread_t pid;
		pthread_cond_t cond;
		pthread_mutex_t _mutex;
		//std::mutex  _mutex;
		std::queue<std::shared_ptr<Task>> Tasks;
	};

	class IMReactor
	{
	public:
		virtual ~IMReactor ();
	
		static IMReactor* getInstances();
		static IMReactor* IMReactorInit(char* IP, uint16_t port);
		static void addEventListen (Event event);
		void eventAdd(Event event);

		void loop();

	private:
		IMReactor (char* IP, uint16_t port);
		int sock_listen;
		int epoll_root;

		size_t event_count;

		void* (*TaskThreadCallBack) (void* arg);

		std::queue<Event> que;
		std::mutex que_mutex;

		std::vector<epoll_event> events;
		std::vector<TaskThread> threads;

		static IMReactor* _thisReactor;
	};

	void* IMTaskCallBack (void* arg);


}

#endif /* end of include guard: IMREACTOR_H_KZTSCYOX */
