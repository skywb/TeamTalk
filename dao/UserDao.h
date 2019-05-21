#ifndef USERDAO_H_SHOUYAFC
#define USERDAO_H_SHOUYAFC

#include "DB.h"

class UserDao : public DBUtil::Dao
{
public:
	virtual ~UserDao () {
	}

	bool _insert(User *user);
	bool _delete(User::Account id);
	bool _update(User *user);
	User* _obtain(User::Account id);

	static bool Insert(User *user) { return getInstance()->_insert(user); }
	static bool Delete(User::Account id) { return getInstance()->_delete(id); }
	static bool Update(User *user) { return getInstance()->_update(user); }
	static User* Obtain(User::Account id) { return getInstance()->_obtain(id); }

private:

	static UserDao* getInstance() {return object;}
	static UserDao* object;

	UserDao (): Dao(MYSQLSERVERURL, MYSQLACCOUNT, MYSQLPASSWORD) {
			conn->createStatement()->execute("use teamtalk");
   	}
};

#endif /* end of include guard: USERDAO_H_SHOUYAFC */
