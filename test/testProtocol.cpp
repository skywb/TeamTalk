#include <iostream>
#include "IM/IMProtocol.h"

using namespace std;

void fun(char* addr, size_t len);

int main()
{


	IM::IMPduHeader pdu;
	pdu.setCommand(IM::IMPduHeader::LOGIN);
	pdu.setUserId(1111);
	pdu.setBodyLength(10);

	

	std::cout << "init" << std::endl;
	std::cout << pdu.getCommand() << std::endl;
	std::cout << pdu.getUserId() << std::endl;
	std::cout << pdu.getBodyLength() << std::endl;

	char buf[100];
	pdu.getHeader(buf);

	IM::IMPduHeader npdu(buf);

	if(npdu.getCommand() == IM::IMPduHeader::INVALID) 
		std::cout << "faild" << std::endl;

	std::cout << "after" << std::endl;
	std::cout << npdu.getCommand() << std::endl;
	std::cout << npdu.getUserId() << std::endl;
	std::cout << npdu.getBodyLength() << std::endl;


	return 0;
}
