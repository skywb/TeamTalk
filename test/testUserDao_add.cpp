#include <iostream>

#include <gtest/gtest.h>

#include "dao/UserDao.h"


TEST(test_UserDao, add)
{
	User *user = new User();
	user->setName("wang");
	user->setId(1003);
	user->setPassword("password");
	user->setFriends("1000;1002");
	bool ok = UserDao::Insert(user);

	ASSERT_TRUE(ok);
}
