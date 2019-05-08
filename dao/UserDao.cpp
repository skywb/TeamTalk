#include <iostream>

#include "UserDao.h"
#include "util/DBUtil.h"



bool UserDao::insert(User *user) {
	
	/*
	 * function:
	 * 向数据库中插入一个user
	 */

	sql::PreparedStatement *pre_stmt;
	try {
	
		pre_stmt = conn->prepareStatement(
				"insert into account values(?, ?, ?, ?)");	

		pre_stmt->setInt(1, user->getId());
		pre_stmt->setString(2, user->getPassword());
		pre_stmt->setString(3, user->getName());
		pre_stmt->setString(4, user->getFriends());

		bool ok = pre_stmt->execute();
		delete pre_stmt;
		return ok;
	}catch(sql::SQLException &e) {
	
		//std::cerr << e.getSQLState() << std::endl;
		std::cerr <<  __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
		if(pre_stmt) delete  pre_stmt;
	}

	return false;

}


User* UserDao::Obtain(User::Account id) {


	/* function:
	 * 从数据库获取id的User信息, 存入User中 
	 * */


	/* 使用智能指针的方式， 报错没有看懂， 可能是因为数据库连接返回的是普通指针， 没有析构函数， 需要自己写智能指针释放时的函数
	 *

	try {
	
		auto stmt = std::make_shared<sql::PreparedStatement> (conn->prepareStatement("select * from account where id=?"));
		
		stmt->setUInt64(1, id);
		auto res = std::make_shared<sql::ResultSet> (stmt->executeQuery());

		auto user = std::make_shared<User> ();

		if(res->next()) {
			user->setId(res->getInt(1));
			user->setPassword(res->getString(2));
			user->setName(res->getString(3));
			user->setFriends(res->getString(4));
		}
		if(user->getId() != id) return nullptr;
		return user.get();

	}catch(sql::SQLException &e) {

		std::cerr <<  __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
	} 

	*/

	sql::PreparedStatement * stmt = nullptr;
	sql::ResultSet *res = nullptr;

	try {
	
		stmt = conn->prepareStatement("select * from account where id=?");
		
		stmt->setUInt64(1, id);
		res = stmt->executeQuery();

		User *user = new User();
		try {

			if(res->next()) {
				user->setId(res->getInt(1));
				user->setPassword(res->getString(2));
				user->setName(res->getString(3));
				user->setFriends(res->getString(4));
			}

		}catch(sql::SQLException &e) {
			std::cerr <<  __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
			if(user) delete user;
		}

		if(user->getId() != id)
		{
			delete user;
			return nullptr;
		}
		delete res;
		delete stmt;
		return user;

	}catch(sql::SQLException &e) {
		if(res) delete res;
		if(stmt) delete stmt;
		std::cerr <<  __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
	} 
	return nullptr;
}
