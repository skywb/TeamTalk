#include <iostream>
#include <unistd.h>

#include "reactor/IMReactor.h"
#include "reactor/task.h"
#include "util/Log.h"

class MyTask : public Task
{
public:
	MyTask() :   Task(std::make_shared<Connecter>  (10))  { }
	virtual ~MyTask () {}

	void doit() {
		std::cout << "hello world" << std::endl;
	}

private:
	/* data */
};

int main()
{
	Log::InitLogThread(nullptr);	

	IM::ThreadPool pool(10);

	pool.start();
	pool.addTask(std::make_shared<MyTask> ());
	::sleep(10);	
	pool.stop();

	return 0;
}
