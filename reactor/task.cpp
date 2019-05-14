#include <iostream>

#include "reactor/task.h"
#include "IM/IMProtocol.h"
#include "IM/login_server.h"

using namespace	IM;

void Task::doit() {

	std::cout << "task doing..." << std::endl;
}


void ReadableTask::doit() {

	while(true) {
		auto pdu = IM::makeIMPdu(p_con);
		if(!pdu) {
			break;
		}
		std::cout << "new Pdu" << std::endl;

		switch (pdu->getCommand()) {
			case IM::LOGIN:
				login_server(std::dynamic_pointer_cast<IM::LoginPdu> (pdu), p_con);
				break;
			case IM::LOGOUT:
				std::cout << "logout" << std::endl;
				break;
			case IM::SENDMSG:
				std::cout << "send message" << std::endl;
				break;
			default:
				std::cout << "what are you doing" << std::endl;
				break;

		}

	}

}

void WriteableTask::doit() {
	/*
	 * 做可写事件处理
	 * 将缓冲区的数据写入套接字内
	 */
	p_con->onWriteable();
}


void NewConnectTask::doit() {
	/* 弃用 
	 * 接受一个或者多个新的连接
	 * 为每个新的连接创建一个connecter， 并添加到sockToConn中
	 * 想监听队列中添加一个需要监听的事件
	 * */

	std::cout << "newConnect task doing..." << std::endl;

}




