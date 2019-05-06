#include <iostream>

#include "IM/IMProtocol.h"
#include "util/sockUtil.h"

#include "util/testUtil.h"

int main()
{
	sockaddr_in addr;
	sockUtil::setNetClientAddr(&addr, "127.0.0.1", 9999);
	int fd = sockUtil::connectToAddr(&addr);
	sockUtil::setNoBlock(fd);

	int cmd;
	std::shared_ptr<IM::IMPdu> pdu;
	char buf[BUFSIZ];
	while(true) {
		//system("clear");
		std::cout << "类型：1.login 2.logout 3.sendmsg" << std::endl;
		std::cin >> cmd;
		IM::IMPdu::UserId id;
		//std::string msg;
		char msg[BUFSIZ];
		size_t msg_len = 0;
		switch (cmd) {
			case 1:
				pdu =  std::make_shared<IM::LoginPdu> ();	
				std::cout << "your ID: ";
				std::cin >> id;
				pdu->setUserId(id);
				char pwd[100];
				std::cout << "密码： ";
				std::cin >> pwd;
				std::dynamic_pointer_cast<IM::LoginPdu> (pdu)->setPassword(pwd);
				break;
			case 2:
				pdu = std::make_shared<IM::Logout> ();
				std::cout << "your ID: ";
				std::cin >> id;
				pdu->setUserId(id);
				break;
			case 3:
				pdu = std::make_shared<IM::SendMsgPdu> ();
				std::cout << "your ID: ";
				std::cin >> id;
				pdu->setUserId(id);
				IM::IMPdu::UserId objId;
				std::cout << "objID : ";
				std::cin >> objId;	
				std::dynamic_pointer_cast<IM::SendMsgPdu> (pdu)->setObjID(objId);
				std::cout << "MSG : ";
				std::cin >> msg;	
				msg_len = strlen(msg);
				std::dynamic_pointer_cast<IM::SendMsgPdu> (pdu)->setBodyMsg(msg, msg_len);
				break;
			default:
				std::cout << "What are you doing?" << std::endl;
				continue;
				break;
		}
		int len = IM::IMPduToSerivlization(buf, pdu);
		std::cout << pdu->getHeaderLenth() << std::endl;
		int re  =  write(fd, buf, len);
		if(re == -1) {
			std::cout << strerror(errno) << std::endl;
		}  else   std::cout << "write " << re << "Byte" << std::endl;
	}
	return 0;
}
