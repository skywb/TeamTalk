#include <iostream>

#include "reactor/task.h"
#include "IM/IMProtocol.h"

#include "util/testUtil.h"

bool fun(std::shared_ptr<Connecter> con) {

	auto pdu = IM::makeIMPdu(con);
	if(!pdu) {
		std::cout << "pdu is nullptr" << std::endl;
		return true;
	}

	std::cout << "base cnt " << pdu.use_count() << std::endl;

	std::shared_ptr<LoginPdu> login = std::dynamic_pointer_cast<LoginPdu> (pdu);
	std::cout << "base cnt " << pdu.use_count() << std::endl;
	std::cout << "child cnt " << login.use_count() << std::endl;

	std::cout << "is Login " << (login->getCommand() == IM::IMPduCMD::LOGIN ? "true" : "false") << std::endl;
	std::cout << "user id is " << login->getUserId() << std::endl;
	std::cout << "password is " << login->getPassword() << std::endl;

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
