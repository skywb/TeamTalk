#include <iostream>

#include "util/Log.h"
#include "reactor/IMReactor.h"


int main(int argc, char *argv[])
{

	Log::InitLogThread(nullptr);
	auto reactor = IM::IMReactor::IMReactorInit(nullptr, 9999);

	reactor->loop();

	reactor = nullptr;
	
	return 0;
}
