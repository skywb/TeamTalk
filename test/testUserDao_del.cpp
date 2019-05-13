#include <iostream>

#include <gtest/gtest.h>
#include "dao/UserDao.h"

TEST(testUserDao, Delete)
{
	bool ok = UserDao::Delete(1002);
	
	ASSERT_TRUE(ok);
	User *user = UserDao::Obtain(1002);
	ASSERT_EQ(user, nullptr);
}


