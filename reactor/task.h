#ifndef TASK_H_TKQEYUJB
#define TASK_H_TKQEYUJB

#include "reactor/Connecter.h"
#include "IM/IMProtocol.pb.h"

using namespace IM;
/*
 * 任务基类， 每个工作线程获得该基类指针，
 * 不同的任务都派生自该基类， 实现doit任务处理函数
 * 在每个工作线程中， 拿到该Task之后调用doit执行任务.
 */
class Task {
	public:
		Task() {}

		virtual void doit() = 0;

		~Task() { }
};

class IMTask : public Task
{
public:
	IMTask (std::shared_ptr<IMConn> connecter_ptr) :
		p_con(connecter_ptr) { }
	virtual ~IMTask () { }

	void doit() override = 0;

protected:
	std::shared_ptr<IMConn> p_con;
};



class WriteableTask : public IMTask
{
	public:
		WriteableTask (std::shared_ptr<IMConn> connecter_ptr) : 
			IMTask(connecter_ptr) { }

		virtual ~WriteableTask () { }

		void doit() override ;

};

class ReadableTask : public IMTask
{
	public:
		ReadableTask (std::shared_ptr<IMConn> connecter_ptr) : 
			IMTask(connecter_ptr) { }

		virtual ~ReadableTask () { }

		void doit() override ;

};

class NewConnectTask : public IMTask
{
	public:
		NewConnectTask (std::shared_ptr<IMConn> connecter_ptr) : 
			IMTask(connecter_ptr) { }

		virtual ~NewConnectTask () { }

		void doit() override ;

};

/*
class LoginTask : public IMTask
{
public:
	LoginTask (std::shared_ptr<IM::LoginPdu> user_p, 
			std::shared_ptr<IMConn> connecter_ptr) : 
		IMTask(connecter_ptr),
		userPdu(user_p) { }
	virtual ~LoginTask () { }

	void doit() override ;

private:
	std::shared_ptr<IM::LoginPdu> userPdu;
};

*/

#endif /* end of include guard: TASK_H_TKQEYUJB */
