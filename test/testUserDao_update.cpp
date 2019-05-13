
#include <gtest/gtest.h>
#include "dao/UserDao.h"

TEST(testUserDao, update)
{
	User user;
	user.setId(1003);
	user.setName("zhangsan");
	user.setPassword("1111");
	user.setFriends("1001");

	ASSERT_EQ(UserDao::Update(&user), 1);


	
}


