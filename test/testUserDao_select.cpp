#include <iostream>

#include <gtest/gtest.h>
#include "dao/UserDao.h"


TEST(testUserDao, select)
{
	User *user = UserDao::Obtain(1002);
	ASSERT_EQ(user->getId(), 1002);
	GTEST_ASSERT_EQ(user->getPassword(), "password");
}




