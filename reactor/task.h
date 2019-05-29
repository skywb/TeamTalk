#ifndef TASK_H_TKQEYUJB
#define TASK_H_TKQEYUJB

#include "reactor/Connecter.h"
#include "IM/IMProtocol.pb.h"
#include "util/Log.h"

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
	//IMTask (std::shared_ptr<IMConn> connecter_ptr) :
	//	p_con(connecter_ptr) { }
	IMTask(const Proto::Request* req) : request_base(req) {
		response_base =  new  Proto::Response();
		p_con =  nullptr;
	}

	virtual ~IMTask () {
		/* 将response返回 */
		try {
			if(p_con) {
				p_con->send(response_base);	
				Log::log(Log::INFO, "send msg to client");
			} else {
				std::cout << "p_con is null" << std::endl;
			}
		}catch(...) {
			Log::log(Log::ERROR, "catch a exception in ~IMTask()");
		}
		delete response_base;
   	}

	void doit() override = 0;

private:
	std::shared_ptr<IMConn> p_con;

protected:
	const Proto::Request* request_base;
	Proto::Response* response_base;
};



class WriteableTask : public Task
{
public:
	WriteableTask (std::shared_ptr<IMConn> connecter_ptr) : 
		p_con(connecter_ptr) { }

	virtual ~WriteableTask () { }

	void doit() override ;
private:
	std::shared_ptr<IMConn> p_con;
};

class ReadableTask : public Task
{
public:
	ReadableTask (std::shared_ptr<IMConn> connecter_ptr) : 
		p_con(connecter_ptr) { }

	virtual ~ReadableTask () { }

	void doit() override ;

private:
	std::shared_ptr<IMConn> p_con;
};


#endif /* end of include guard: TASK_H_TKQEYUJB */
