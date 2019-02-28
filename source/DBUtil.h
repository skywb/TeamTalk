#ifndef DBUTIL_H_7OLYEVBA
#define DBUTIL_H_7OLYEVBA

#include <mysql/jdbc/mysql_driver.h>
#include <mysql/jdbc/cppconn/connection.h>
#include <mysql/jdbc/cppconn/statement.h>



#define MYSQLSERVERURL "tcp://127.0.0.1:3306"
#define MYSQLACCOUNT "root"
#define MYSQLPASSWORD "root"

#include "User.h"

namespace DBUtil {
	class Dao
	{
	public:
		Dao (const char* hostname, const char* userName, const char* password) {
			driver = sql::mysql::get_driver_instance();
			conn = driver->connect(hostname, userName, password);
		}
		virtual ~Dao () {
			delete conn;
		}
	
	protected:
		sql::Driver *driver;
		sql::Connection *conn;
		sql::Statement *stmt;
	};

	class UserDao : public Dao
	{
	public:
		UserDao (): Dao(MYSQLSERVERURL, MYSQLACCOUNT, MYSQLPASSWORD) {
			stmt = conn->createStatement();
		}
		virtual ~UserDao () {
			delete stmt;
		}

		bool insert(User *user);
		User* Obtain(User::Account id);

	};
}

#endif /* end of include guard: DBUTIL_H_7OLYEVBA */