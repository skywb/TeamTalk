#include <iostream>
#include <map>
#include <pthread.h>

#include "User.h"
#include "reactor/Connecter.h"
#include "IM/IMProtocol.h"



class SockMap
{
public:
	virtual ~SockMap () {
		::pthread_mutex_destroy(&m_mutex);
	}

	static void init() {
		object_p = new SockMap();
	}

	static int findSocketById(int fd) {
		if(object_p == nullptr) init();
		return object_p->findId(fd);
	}

	static bool addAccount(std::pair<User::Account, int> p) {
		if(object_p == nullptr) init();
		return object_p->add(p);
	}

	static bool delAccount(std::pair<User::Account, int> p) {
		if(object_p == nullptr) init();
		return object_p->del(p);
	}
	int findId(int fd);
	bool add(std::pair<User::Account, int> p);
	bool del(std::pair<User::Account, int> p);

private:
	SockMap () {
		::pthread_mutex_init(&m_mutex, nullptr);
	}
	static SockMap* object_p;
	std::map<User::Account, int> m_map;
	pthread_mutex_t m_mutex;

};

void login_server(std::shared_ptr<IM::LoginPdu> pdu);
