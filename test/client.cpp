#include <iostream>
#include <thread>

#include "reactor/IMReactor.h"
#include "reactor/Connecter.h"
#include "IM/IMProtocol.pb.h"
#include "IM/User.h"


void reciveMsg(ClientConn* con) {
	while(true) {
		auto response = con->recive();
		while (response == nullptr){ 
			con->waitMsg();
			response = con->recive();
		}
		if(!response) {
			std::cout << "response is null" << std::endl;
			continue;
		}
		switch (response->type()) {
			case Proto::Response_Type_LOGIN:
				{
					std::cout << "login" << std::endl;	
					if(!response->has_response_login()) {
						std::cout << "not has login" << std::endl;
						break;
					}

					auto stat = response->response_login();
					switch (stat.stat()) {
						case Proto::Response_login_STAT_SUCCESS:
							std::cout << "登录成功" << std::endl;
							std::cout << stat.friends() << std::endl;
							break;
						case Proto::Response_login_STAT_PASSWORD_ERROR:
							std::cout << "密码错误" << std::endl;	
							break;
						case Proto::Response_login_STAT_ACCOUNT_NULL:
							std::cout << "账号不存在" << std::endl;	
							break;
						default:
							std::cout << "error" << std::endl;
							break;
					}
				}
				break;
			case Proto::Response_Type_FriendInfo:
				{
					std::cout << "friend info" << std::endl;
					if(!response->has_response_friendinfo()) {
						std::cout << "not has info" << std::endl;
						break;
					}
					auto  info = response->response_friendinfo();
					std::cout << "id " << info.id() << std::endl;
					std::cout << "name " << info.info().name() << std::endl;
				}
				break;
			case Proto::Response_Type_SENDMSG:
				{
					std::cout << "send msg response" << std::endl;
					if (!response->has_response_sendmsg()) {
						std::cout << "not has msg response" << std::endl;
						break;
					}
					auto res = response->response_sendmsg();
					std::cout << "stat " << res.stat() << std::endl;
				}
				break;
			case Proto::Response_Type_MESSAGE:
			{
				std::cout << "recive new message " << std::endl;

				if (!response->has_msg()) {
					std::cout << "not has msg" << std::endl;
					break;
				}
				auto msg = response->msg();
				std::cout << "from : " << msg.fromid() << std::endl;
				std::cout << "to : " << msg.toid() << std::endl;
				std::cout << "message : " << msg.msg() << std::endl;
			}
					break;
			default:
				std::cout << "other" << std::endl;
				break;
		}

	}

}



int main()
{
	ClientConn con("127.0.0.1", 9999);
	std::thread th(reciveMsg, &con);

	int cmd;
	Proto::Request* request = new Proto::Request();
	User user;

	while(true) {
		//system("clear");
		std::cout << "类型：1.login 2.getFriend 3.sendmsg" << std::endl;
		std::cin >> cmd;
		switch (cmd) {
			case 1:
			{
				User::Account id;
				auto  login = new Proto::Request_login();
				std::cout << "your ID: ";
				std::cin >> id;
				user.setId(id);
				login->set_id(id);
				char pwd[100];
				std::cout << "密码： ";
				std::cin >> pwd;
				user.setPassword(pwd);
				login->set_password(pwd);
				request->set_allocated_request_login(login);
				con.send(request);
			}
				break;
			case 2:
			{
				request->set_type(Proto::Request_Type_FriendInfo);
				auto getFriend  = new Proto::Request_FriendInfo();
				getFriend->set_fromid(1000);
				getFriend->set_friendid(1002);
				request->set_allocated_request_friendinfo(getFriend);
				con.send(request);
			}
				break;
			case 3:
			{
				request->set_type(Proto::Request_Type_SENDMSG);
				auto send = new Proto::Request_sendmsg();
				send->set_id(user.getId());
				User::Account objId;
				std::cout << "objID : ";
				std::cin >> objId;	
				send->set_objid(objId);
				std::string msg;
				std::cout << "MSG : ";
				getchar();
				std::getline(std::cin, msg);
				send->set_msg(msg);
				request->set_allocated_request_sendmsg(send);
				con.send(request);
				break;
			}
			default:
				std::cout << "What are you doing?" << std::endl;
				continue;
				break;
		}
	}

	return 0;
}
