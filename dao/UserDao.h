#ifndef USERDAO_H_SHOUYAFC
#define USERDAO_H_SHOUYAFC

#include <mysql/jdbc/mysql_driver.h>
#include <mysql/jdbc/cppconn/driver.h>
#include <mysql/jdbc/cppconn/connection.h>
#include <mysql/jdbc/cppconn/statement.h>


#include "IM/User.h"
#include "util/DBUtil.h"

#define MYSQLSERVERURL "tcp://127.0.0.1:3306"
#define MYSQLACCOUNT "root"
#define MYSQLPASSWORD "root"


class UserDao : public DBUtil::Dao
{
	public:
		UserDao (): Dao(MYSQLSERVERURL, MYSQLACCOUNT, MYSQLPASSWORD) {
		}
		virtual ~UserDao () {
		}

		bool insert(User *user);
		User* Obtain(User::Account id);

};

#endif /* end of include guard: USERDAO_H_SHOUYAFC */
