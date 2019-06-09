#include <boost/date_time/posix_time/posix_time.hpp>

#include "MsgDao.h"

MsgDao *MsgDao::object = new MsgDao();


bool MsgDao::_insert(Proto::Message* msg) {
	
	/*
	 * function:
	 * 向数据库中插入一个msg
	 */

	sql::PreparedStatement *pre_stmt;
	try {
	
		pre_stmt = conn->prepareStatement(
				"insert into messages values(null, ?, ?, ?, ?, ?, ?)");	
		pre_stmt->setInt(1, msg->fromid());
		pre_stmt->setInt(2, msg->toid());
		pre_stmt->setString(3, msg->msg());
		pre_stmt->setBoolean(4, msg->recived());
		pre_stmt->setInt(5, 1);
		
		//获取当前时间
		char curTime[32];
		time_t now = time(nullptr);
		strftime(curTime, 32, "%Y-%m-%d %H:%M:%S", localtime(&now));
		pre_stmt->setDateTime(6, curTime);

		int re  = pre_stmt->executeUpdate();
		delete pre_stmt;
		return (re == 1);
	}catch(sql::SQLException &e) {
	
		//std::cerr << e.getSQLState() << std::endl;
		std::cerr <<  __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
		if(pre_stmt) delete pre_stmt;
	}

	return false;

}

Proto::Message* _obtain(int id) {

	return nullptr;
}
