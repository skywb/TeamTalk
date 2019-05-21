#ifndef FRIENDDAO_H_VJPAYB9E
#define FRIENDDAO_H_VJPAYB9E

#include "DB.h"

class FriendDao : public DBUtil::Dao
{
public:
	virtual ~FriendDao () { }

	/* TODO:  <21-05-19, yourname> */
	std::vector<std::pair<User::Account, int>> getAllFriendsByID(User::Account id);
	bool addFriend(User::Account id, User::Account friendID);
	bool delFriend(User::Account id, User::Account friendID);

	

private:
	static FriendDao* getInstance() {return object;}
	static FriendDao* object;

	FriendDao (): Dao(MYSQLSERVERURL, MYSQLACCOUNT, MYSQLPASSWORD) {
			conn->createStatement()->execute("use teamtalk");
   	}
	
};



#endif /* end of include guard: FRIENDDAO_H_VJPAYB9E */
