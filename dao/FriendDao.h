#ifndef FRIENDDAO_H_VJPAYB9E
#define FRIENDDAO_H_VJPAYB9E

#include "DB.h"

class FriendDao : public DBUtil::Dao
{
public:
	virtual ~FriendDao () { }

	std::vector<std::pair<User::Account, int>> getAllFriendsByID(User::Account id);
	bool addFriend(User::Account id, User::Account friendID, int groupIDInThisAccount = 1);
	bool delFriend(User::Account id, User::Account friendID);

	std::string getGroupNameByID(int ID);
	std::string getGroupNameByID(User::Account UserID, int groupIDInUser);
	bool updateGroupName(User::Account userID, int groupIdInThisUser, const std::string name);
	bool delGroup(User::Account userID, int groupIdInThisUser);
	int addGroup(User::Account userID, const std::string groupName);
	
	static FriendDao* getInstance() {return object;}

private:
	static FriendDao* object;

	FriendDao (): Dao(MYSQLSERVERURL, MYSQLACCOUNT, MYSQLPASSWORD) {
			conn->createStatement()->execute("use teamtalk");
   	}
	
};



#endif /* end of include guard: FRIENDDAO_H_VJPAYB9E */
