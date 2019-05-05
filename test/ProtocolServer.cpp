#include <iostream>

#include "util/Log.h"
#include "reactor/IMReactor.h"
#include "IM/IMProtocol.h"
#include "reactor/Connecter.h"


int main()
{

	Log::InitLogThread(nullptr);
	auto reactor = IM::IMReactor::IMReactorInit(nullptr, 9999);

	reactor->loop();



	
	return 0;
}
