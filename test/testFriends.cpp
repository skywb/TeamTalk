#include <gtest/gtest.h>
#include "dao/FriendDao.h"


int main()
{

//	auto dao = FriendDao::getInstance();	
//	dao->addFriend(1000, 1003, 1);
	auto dao = FriendDao::getInstance();	
	//dao->addFriend(1000, 1003, 1);
	//dao->delFriend(1000, 1002);
	std::cout <<  dao->getGroupNameByID(1000, 1) << std::endl;

	//dao->updateGroupName(1000, 1, "myfriends");
	//dao->delGroup(1002, 1);
	dao->addGroup(1000, "second Group");

	return 0;
}
