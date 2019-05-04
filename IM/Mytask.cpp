#include <iostream>
#include "reactor/task.h"
#include "IM/IMProtocol.h"

void fun(std::shared_ptr<Connecter> con) {
	con->startTryRecive();
	auto header = IM::IMPduHeader::makeHeader(con);
	if(header->getCommand() != IM::IMPduHeader::INVALID) {
		std::cout << "cmd = ";
		if(header->getCommand() == IM::IMPduHeader::LOGIN) {
			std::cout << "login" << std::endl;
		} else if(header->getCommand() == IM::IMPduHeader::LOGOUT) {
			std::cout << "logout" << std::endl;

		} else if(header->getCommand() == IM::IMPduHeader::SENDMSG) {
			std::cout << "send msg" << std::endl;
		}

		std::cout << "userId = " <<  header->getUserId() << std::endl;
		std::cout << "body length = " << header->getBodyLength() << std::endl;
	}

	con->send("recived your msg");


}



void ReadableTask::doit() {

	fun(p_con);


	/* TODO: 
	 * 
	 * 1. 读取最少一个协议头
	 * 2. 读取消息
	 * 3. 判断是否还有未读信息， 有则循环
	 * 4. 执行对应的处理函数
	 * 5. 若不足一个协议头则返回nullprt  跳过
	 * <24-04-19, sky> */


}
