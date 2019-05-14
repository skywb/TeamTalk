#include <iostream>
#include <map>
#include <pthread.h>

#include "User.h"
#include "reactor/Connecter.h"
#include "IM/IMProtocol.h"



class ConnMap
{
public:
	virtual ~ConnMap () {
		::pthread_mutex_destroy(&m_mutex);
	}

	//static void init() {
	//	object_p = new SockMap();
	//}

	//根据用户ID返回Connecter
	//若用户不在线则返回-1
	static std::shared_ptr<IM::Connecter> findConnecterById(int id) {
		if(object_p == nullptr) {
			std::cout << "object_p is nullptr" << std::endl;
		}
		return object_p->find(id);
	}

	//添加一个在线用户
	//若已经在线返回false
	static std::shared_ptr<IM::Connecter> addAccount(std::pair<User::Account, std::shared_ptr<IM::Connecter>> p) {
		if(object_p == nullptr) {
			std::cout << "object_p is nullptr" << std::endl;
		}
		return object_p->add(p);
	}

	//删除一个在线用户
	//若用户不在线， 返回false
	static bool delAccount(std::pair<User::Account, std::shared_ptr<IM::Connecter>> p) {
		if(object_p == nullptr) {
			std::cout << "object_p is nullptr" << std::endl;
		}
		return object_p->del(p);
	}
	std::shared_ptr<IM::Connecter> find(int fd);
	std::shared_ptr<IM::Connecter> add(std::pair<User::Account, std::shared_ptr<IM::Connecter>> p);
	bool del(std::pair<User::Account, std::shared_ptr<IM::Connecter>> p);

private:
	ConnMap () {
		::pthread_mutex_init(&m_mutex, nullptr);
	}
	static ConnMap* object_p;
	std::map<User::Account, std::shared_ptr<IM::Connecter>> m_map;
	pthread_mutex_t m_mutex;

};

void login_server(std::shared_ptr<IM::LoginPdu> pdu, std::shared_ptr<IM::Connecter> con);
