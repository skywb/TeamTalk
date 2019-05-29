#include "reactor/IMReactor.h"
#include "IM/IMProtocol.pb.h"
#include "IM/User.h"

int main()
{
	ClientConn con("127.0.0.1", 9999);

	int cmd;
	Proto::Request* request = new Proto::Request();

	char buf[BUFSIZ];
	while(true) {
		//system("clear");
		std::cout << "类型：1.login 2.getFriend 3.sendmsg" << std::endl;
		std::cin >> cmd;
		char msg[BUFSIZ];
		size_t msg_len = 0;
		switch (cmd) {
			case 1:
			{
				User::Account id;
				auto  login = new Proto::Request_login();
				std::cout << "your ID: ";
				std::cin >> id;
				login->set_id(id);
				char pwd[100];
				std::cout << "密码： ";
				std::cin >> pwd;
				login->set_password(pwd);
				request->set_allocated_request_login(login);
				con.send(request);
			}
				break;
			case 2:
			{
				User::Account id;
				request->set_type(Proto::Request_Type_FriendInfo);
				auto getFriend  = new Proto::Request_FriendInfo();
				getFriend->set_fromid(1000);
				getFriend->set_friendid(1002);
				request->set_allocated_request_friendinfo(getFriend);
				con.send(request);
			}
				break;
			case 3:
				//pdu = std::make_shared<IM::SendMsgPdu> ();
				//std::cout << "your ID: ";
				//std::cin >> id;
				//pdu->setUserId(id);
				//IM::IMPdu::UserId objId;
				//std::cout << "objID : ";
				//std::cin >> objId;	
				//std::dynamic_pointer_cast<IM::SendMsgPdu> (pdu)->setObjID(objId);
				//std::cout << "MSG : ";
				//std::cin >> msg;	
				//msg_len = strlen(msg);
				//std::dynamic_pointer_cast<IM::SendMsgPdu> (pdu)->setBodyMsg(msg, msg_len);
				break;
			default:
				std::cout << "What are you doing?" << std::endl;
				continue;
				break;
		}

		sleep(2);
		auto response = con.recive();
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
			default:
			std::cout << "other" << std::endl;
			break;
		}

	}
	
	delete request;
	return 0;
}
