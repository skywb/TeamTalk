#include <iostream>

#include "reactor/IMReactor.h"
#include "reactor/task.h"
#include "dao/UserDao.h"
#include "util/Log.h"
#include "server/loginTask.h"

using namespace	IM;



void ReadableTask::doit() {

	std::cout << "ReadableTask" << std::endl;		
	while(true) {
		auto request = p_con->recive();
		if(!request) {
			break;
		}
		switch (request->type()) {
			case Proto::Request_Type_LOGIN:
				if(!request->has_request_login()) {
					Log::log(Log::ERROR, "协议格式错误");
				}

				{
					const Proto::Request_login& request_login = request->request_login();
					std::cout << "login id: " << request_login.id() << std::endl;
					std::cout << "login password: " << request_login.password() << std::endl;
					LoginTask task(request, p_con);
					task.doit();
					//delete request;
				}
				break;
			case Proto::Request_Type_FriendInfo:
				{
					std::cout << "get friend info" << std::endl;
					GetFriendInfoTask task(request);
					task.doit();
				}
					break;
			case Proto::Request_Type_LOGOUT:
				break;
			case Proto::Request_Type_SENDMSG:
				break;
			default:
				break;
				
		}



		//switch (pdu->getCommand()) {
		//	case IM::LOGIN:
		//		::IMReactor::getInstances()->addTask(
		//				std::make_shared<LoginTask>(std::dynamic_pointer_cast<IM::LoginPdu> (pdu), p_con));
		//		break;
		//	case IM::LOGOUT:
		//		std::cout << "logout" << std::endl;
		//		break;
		//	case IM::SENDMSG:
		//		std::cout << "send message" << std::endl;
		//		break;
		//	default:
		//		std::cout << "what are you doing" << std::endl;
		//		break;

		//}

	}

}

void WriteableTask::doit() {
	/*
	 * 做可写事件处理
	 * 将缓冲区的数据写入套接字内
	 */
	p_con->onWriteable();
}


//void NewConnectTask::doit() {
//	/* 弃用 
//	 * 接受一个或者多个新的连接
//	 * 为每个新的连接创建一个connecter， 并添加到sockToConn中
//	 * 想监听队列中添加一个需要监听的事件
//	 * */
//
//	std::cout << "newConnect task doing..." << std::endl;
//
//}

