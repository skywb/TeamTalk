#include "User.h"


void User::splitFriends() {
	friends_ptr = std::make_shared<std::vector<Account>> ();
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
	/* TODO:  <03-03-19, yourname> */
}
