#include <iostream>
#include "reactor/task.h"
#include "IM/IMProtocol.h"

#include "util/testUtil.h"

bool fun(std::shared_ptr<Connecter> con) {
	//con->startTryRecive();
	std::cout << "start..." << std::endl;

	char buf[BUFSIZ];
	int minLength = sizeof(IM::HEADER_BEGIN) + sizeof(size_t);
	con->startTryRecive(minLength, BUFSIZ);

	int re = con->tryRecive(buf, minLength);
	if(re == 0) 
	{
		con->rollback_tryRecive();
		return true;
	}

	size_t len = *(size_t*)(buf+sizeof(HEADER_BEGIN));

	if(0 == con->tryRecive(buf+minLength, len-minLength)) {
		con->rollback_tryRecive();
		return true;
	}
	con->commit_tryRecive();


	IMPduHeader* header = new IMPduHeader(buf);

	if(header == nullptr) 
	{
		std::cout << "header is nullptr" << std::endl;
		con->rollback_tryRecive();
		return true;
	}
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
	std::cout << "send " << con->send("recived your msg") << std::endl;
	return false;

}



void ReadableTask::doit() {

	while(!fun(p_con));


	/* TODO: 
	 * 
	 * 1. 读取最少一个协议头
	 * 2. 读取消息
	 * 3. 判断是否还有未读信息， 有则循环
	 * 4. 执行对应的处理函数
	 * 5. 若不足一个协议头则返回nullprt  跳过
	 * <24-04-19, sky> */


}
