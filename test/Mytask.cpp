#include <iostream>

#include "reactor/task.h"
#include "IM/IMProtocol.h"

#include "IM/login_server.h"

//bool fun(std::shared_ptr<Connecter> con) {
//
//	auto pdu = IM::makeIMPdu(con);
//	if(!pdu) {
//		std::cout << "pdu is nullptr" << std::endl;
//		return true;
//	}
//
//	char buf[BUFSIZ];
//	switch (pdu->getCommand()) {
//		case IM::LOGIN:
//			std::cout << "CDM: LOGIN" << std::endl;	
//			std::cout << "ID: " << pdu->getUserId() << std::endl;
//			std::cout << "PWD: " << std::dynamic_pointer_cast<IM::LoginPdu> (pdu)->getPassword() << std::endl;
//			break;
//		case IM::LOGOUT:
//			std::cout << "CDM: LOGOUT" << std::endl;	
//			std::cout << "ID: " << pdu->getUserId() << std::endl;
//			break;
//		case IM::SENDMSG:
//			std::cout << "CDM: SENDMSG" << std::endl;	
//			std::cout << "ID:  " << pdu->getUserId() << std::endl;
//			std::cout << "ObjID:  " <<  std::dynamic_pointer_cast<IM::SendMsgPdu>(pdu)->getObjID() << std::endl;
//			std::cout << "MSG: " << std::dynamic_pointer_cast<IM::SendMsgPdu>(pdu)->getBodyMsg(buf) << std::endl;	
//			break;
//		default:
//			std::cout << "无法识别" << std::endl;
//			break;
//	}
//	return false;
//}



//void ReadableTask::doit() {
//
//	while(true) {
//		auto pdu = IM::makeIMPdu(p_con);
//		if(!pdu) {
//			break;
//		}
//
//		switch (pdu->getCommand()) {
//			case IM::LOGIN:
//				login_server(std::dynamic_pointer_cast<IM::LoginPdu> (pdu), p_con);
//				break;
//			case IM::LOGOUT:
//				std::cout << "logout" << std::endl;
//				break;
//			case IM::SENDMSG:
//				std::cout << "send message" << std::endl;
//				break;
//			default:
//				std::cout << "what are you doing" << std::endl;
//				break;
//
//		}
//
//	}
//
//}


