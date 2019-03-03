#include <iostream>
#include "DBUtil.h"


int main()
{
	DBUtil::UserDao userDao;
	User *user;
	user = userDao.Obtain(1002UL);

	std::cout << user->getName() << std::endl;

	delete user;

	return 0;
}
