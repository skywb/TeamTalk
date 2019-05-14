#include <iostream>


#include "util/Log.h"
#include "reactor/Addresser.h"
#include <reactor/IMReactor.h>



int main()
{

	Log::InitLogThread(nullptr);
	auto reactor = IM::IMReactor::IMReactorInit(nullptr, 9999);

	reactor->loop();
	
	return 0;
}
