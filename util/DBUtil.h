#ifndef DBUTIL_H_7OLYEVBA
#define DBUTIL_H_7OLYEVBA

#include <mysql/jdbc/mysql_driver.h>
#include <mysql/jdbc/cppconn/driver.h>
#include <mysql/jdbc/cppconn/connection.h>
#include <mysql/jdbc/cppconn/statement.h>
#include <mysql/jdbc/cppconn/prepared_statement.h>



#define MYSQLSERVERURL "tcp://127.0.0.1:3306"
#define MYSQLACCOUNT "root"
#define MYSQLPASSWORD "root"


namespace DBUtil {

class Dao
{
	public:
		virtual ~Dao () {
			delete conn;
		}

	protected:
		sql::Driver *driver;
		sql::Connection *conn;
		Dao (const char* hostname, const char* userName, const char* password) {
			driver = sql::mysql::get_driver_instance();
			conn = driver->connect(hostname, userName, password);
			conn->createStatement()->execute("use teamtalk");
		}
};

}


#endif /* end of include guard: DBUTIL_H_7OLYEVBA */
