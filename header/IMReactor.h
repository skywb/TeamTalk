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

#include "sockUtil.h"


namespace IM {
	/* TODO:  <05-04-19, yourname> */
	class Event;
	/* TODO:  <05-04-19, yourname> */
	class Task;

	class TaskThread
	{
	public:
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

		void loop();

	private:
		IMReactor (char* IP, uint16_t port);
		int sock_listen;
		int epoll_root;

		void* (*TaskThreadCallBack) (void* arg);

		std::queue<Event> que;
		std::mutex que_mutex;

		
		std::vector<TaskThread> threads;


		static IMReactor* _thisReactor;
	};

	void* IMTaskCallBack (void* arg);


}

#endif /* end of include guard: IMREACTOR_H_KZTSCYOX */
