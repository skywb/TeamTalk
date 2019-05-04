#ifndef TASK_H_TKQEYUJB
#define TASK_H_TKQEYUJB

#include "reactor/Connecter.h"

using namespace IM;
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



#endif /* end of include guard: TASK_H_TKQEYUJB */
