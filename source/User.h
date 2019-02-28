#ifndef USER_H_9YZLOATV
#define USER_H_9YZLOATV

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unistd.h>


class User
{
public:
	typedef unsigned int Account;
	User (Account id = 0) : id(id), friends_ptr(nullptr) {
		_mutex = PTHREAD_MUTEX_INITIALIZER;
	}
	virtual ~User () {
		pthread_mutex_destroy(&_mutex);
	}
	
	Account getId() { return id; }
	void setId(Account ID) { id = ID;}

	std::string getName() { return name; }
	void setName(std::string userName) { name = userName; }

	bool passwordIsEqual(std::string psw) { return psw == password; }
	void setPassword(std::string psw) { password = psw; }

	std::shared_ptr<std::vector<Account> > getFriends() {
		/* TODO: 加锁 */
		if(friends_ptr) return friends_ptr;
		else {
			if(friends.empty()) return nullptr;
			splitFriends();
			return friends_ptr;
		}
	}

	void setFriends(std::string fs) { friends = fs; }

private:
	Account id;
	std::string name;
	std::string password;
	std::string friends;
	std::shared_ptr<std::vector<Account> > friends_ptr;
	pthread_mutex_t _mutex;

	void splitFriends();
};



void User::splitFriends() {
	friends_ptr = std::make_shared<std::vector<Account>>(new std::vector<Account>);
	auto &p = friends_ptr;
	Account tmp = 0;
	for(auto it = friends.begin(); it != friends.end(); ++it)
		if(*it != ';') {
			tmp *= 10;
			tmp += *it - '0';
		} else {
			p->push_back(tmp);
			tmp = 0;
		}
	p->push_back(tmp);
}

#endif /* end of include guard: USER_H_9YZLOATV */
