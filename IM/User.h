#ifndef USER_H_9YZLOATV
#define USER_H_9YZLOATV

#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>
#include <vector>

#include "IM/IMProtocol.h"


class User
{
public:
	typedef unsigned int Account;

	User (Account id = 0) : id(id){ }
	virtual ~User () { }
	
	Account getId() { return id; }
	void setId(Account ID) { id = ID;}

	std::string getName() { return name; }
	void setName(std::string userName) { name = userName; }

	bool passwordIsEqual(std::string psw) { return psw == password; }
	void setPassword(std::string psw) { password = psw; }
	std::string getPassword() { return password;}

	std::string getFriends() {
		return friends;
	}
	void setFriends(const char* friends) {
		this->friends = friends;
	}
	void setFriends(const std::string friends) {
		this->friends = friends;
	}

	//std::shared_ptr<std::vector<Account> > getFriends() {
	//	/* TODO: 加锁 */
	//	if(friends_ptr) return friends_ptr;
	//	else {
	//		if(friends.empty()) return nullptr;
	//		splitFriends();
	//		return friends_ptr;
	//	}
	//}


private:
	Account id;
	std::string name;
	std::string password;
	std::string friends;
	//std::shared_ptr<std::vector<Account> > friends_ptr;

	void splitFriends();
};




#endif /* end of include guard: USER_H_9YZLOATV */
