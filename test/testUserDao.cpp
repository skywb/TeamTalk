#include <iostream>

#include <gtest/gtest.h>

#include "dao/UserDao.h"


TEST(test_User_dao, select)
{
	auto* user = UserDao::Obtain(1000);
	ASSERT_TRUE(user->getId() == 1000) << user->getId();
	ASSERT_TRUE(user->getPassword() == "123");
	ASSERT_TRUE(user->getName() == "test") << user->getName();
}




TEST(test_User_dao, deleteUser)
{
	ASSERT_FALSE(UserDao::Delete(1002));
}


