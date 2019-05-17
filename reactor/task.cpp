#include <iostream>

#include "reactor/IMReactor.h"
#include "reactor/task.h"
#include "IM/IMProtocol.h"
#include "IM/login_server.h"
#include "dao/UserDao.h"

using namespace	IM;



void ReadableTask::doit() {

	while(true) {
		auto pdu = IM::makeIMPdu(p_con);
		if(!pdu) {
			break;
		}
		//std::cout << "new Pdu" << std::endl;

		switch (pdu->getCommand()) {
			case IM::LOGIN:
				::IMReactor::getInstances()->addTask(
						std::make_shared<LoginTask>(std::dynamic_pointer_cast<IM::LoginPdu> (pdu), p_con));
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


void LoginTask::doit() {
	User user;
	user.setId(userPdu->getUserId());
	user.setPassword(userPdu->getPassword());


	auto userConn = ConnMap::findConnecterById(user.getId());
	if(userConn != nullptr) {
		/* TODO: 
		 * 顶掉线
		 * <17-05-19, sky> */
		std::cout << "用户已在线" << std::endl;
		return ;
	}

	User* dbUser = UserDao::Obtain(user.getId());

	//账号不存在
	if(dbUser == nullptr) {
		//std::cout << "账号不存在" << std::endl;
		p_con->send("账号不存在");
		return ;
	}
	//登录成功
	if(user.getPassword() == dbUser->getPassword()) {

		//std::cout << "登录成功" << std::endl;
		p_con->send("登录成功");
		ConnMap::addAccount(std::make_pair(user.getId(), p_con));

	} else { //密码错误

		//std::cout << "密码错误" << std::endl;
		p_con->send("密码错误");
   	}

	/* TODO: 
	 * 从数据库获取user信息
	 * 对比密码
	 * 登录成功则插入sockmap中
	 * 否则返回错误信息
	 * <08-05-19, sky> */
}


