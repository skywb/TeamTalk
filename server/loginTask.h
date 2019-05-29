#ifndef LOGINTASK_H_SC9GCIS2
#define LOGINTASK_H_SC9GCIS2

#include <iostream>
#include <map>
#include <pthread.h>

#include "IM/IMProtocol.pb.h"
#include "reactor/Connecter.h"
#include "reactor/task.h"
#include "IM/User.h"



class ConnMap
{
	public:
		virtual ~ConnMap () { }

		//根据用户ID返回Connecter
		//若用户不在线则返回-1
		static std::shared_ptr<IM::IMConn> findConnecterById(User::Account id) {
			if(object_p == nullptr) {
				std::cout << "object_p is nullptr" << std::endl;
			}
			return object_p->find(id);
		}

		//添加一个在线用户
		//若已经在线返回false
		static std::pair<bool, std::shared_ptr<IM::IMConn>> addAccount(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p) {

			if(object_p == nullptr) {
				std::cout << "object_p is nullptr" << std::endl;
			}
			return object_p->add(p);
		}

		//删除一个在线用户
		//若用户不在线， 返回false
		static bool delAccount(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p) {
			if(object_p == nullptr) {
				std::cout << "object_p is nullptr" << std::endl;
			}
			return object_p->del(p);
		}
		std::shared_ptr<IM::IMConn> find(int fd);
		std::pair<bool, std::shared_ptr<IM::IMConn>> add(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p);
		bool del(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p);

	private:
		ConnMap () { }
		static ConnMap* object_p;
		std::map<User::Account, std::weak_ptr<IM::IMConn>> m_map;
		std::mutex m_mutex;
};




/*
class LoginTask : private IMTask {
	public:
		//LoginTask (const Proto::Request_login& req,
		//	   	Proto::Response_login& rep) : request(req), response(rep)  {}

		LoginTask(const Proto::Request* req) : IMTask(req), request(req->request_login()) {
			response =  new  Proto::Response_login();
		}
		virtual ~LoginTask () {
			response_base->set_allocated_response_login(response);
		}

		void doit() override;

	private:
		const Proto::Request_login& request;
		Proto::Response_login* response;

};
*/

class LoginTask : private Task {
	public:
		//LoginTask (const Proto::Request_login& req,
		//	   	Proto::Response_login& rep) : request(req), response(rep)  {}

		LoginTask(const Proto::Request* req, std::shared_ptr<IM::IMConn> ptr): p_con(ptr), request(req) { }
		virtual ~LoginTask () { }

		void doit() override;

	private:
		std::shared_ptr<IM::IMConn> p_con;
		const Proto::Request* request;
		Proto::Response* response;

};



/*
 * 获取账号信息
 * 用途：
 *	1. 查找好友
 *	2. 同步好友信息
 */
class GetFriendInfoTask : public Task
{
	public:
		GetFriendInfoTask(const  Proto::Request* req) : request(req)  {

		}
		//GetFriendInfoTask(const Proto::Request* req) : IMTask(req), request(req->request_friendinfo()) {
		//	response =  new  Proto::Response_FriendInfo();
		//}
		virtual ~GetFriendInfoTask () {

		}
		void doit() override;
	private:
		const  Proto::Request* request;
		Proto::Response* response;
};





#endif /* end of include guard: LOGINTASK_H_SC9GCIS2 */
