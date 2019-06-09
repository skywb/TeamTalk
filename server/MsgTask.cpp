#include "MsgTask.h"
#include "util/Log.h"
#include "dao/MsgDao.h"

void MsgTask::doit() {
	Log::log(Log::INFO, "recive sendmsg request");
	#ifdef NDEBUG
	std::cout << "recive sendmsg request" << std::endl;
	#endif
	response = new Proto::Response();
	if(!request->has_request_sendmsg()) 
	{
		Log::log(Log::ERROR, "not has request sendmsg");
		return;
	}
	response->set_type(Proto::Response_Type_SENDMSG);
	auto msg = request->request_sendmsg();
	auto fromId = msg.id();
	if(p_con != ConnMap::findConnecterById(fromId)) {
		//不在线
		auto stat = new Proto::Response_sendmsg();
		stat->set_stat(false);
		//stat->set_errmsg("not login");
		response->set_allocated_response_sendmsg(stat);
		p_con->send(response);
		Log::log(Log::INFO, "recive sendmsg request but not login");
		#ifdef NDEBUG
			std::cout << "not login" << std::endl;
		#endif

		return ;
	} 

	auto objId = msg.objid();
	//未判断是否为真实用户
	if(ConnMap::userIsOnline(objId)) {
		//对方在线, 直接发送给用户
		auto objRe = new Proto::Response();
		objRe->set_type(Proto::Response_Type_MESSAGE);
		auto objmsg = new Proto::Message();
		objmsg->set_msg(msg.msg());
		objmsg->set_fromid(msg.id());
		objmsg->set_toid(msg.objid());
		objmsg->set_recived(true);
		//插入数据库
		MsgDao::Insert(objmsg);

		objRe->set_allocated_msg(objmsg);
		auto objCon = ConnMap::findConnecterById(objId);
		objCon->send(objRe);

		auto msgre = new Proto::Response_sendmsg();
		msgre->set_stat(true);
		msgre->set_msgid(1);
		response->set_allocated_response_sendmsg(msgre);
		p_con->send(response);
		#ifdef NDEBUG
			std::cout << "sendmsg succed" << std::endl;
		#endif
	} else {
		auto objmsg = new Proto::Message();
		objmsg->set_msg(msg.msg());
		objmsg->set_fromid(msg.id());
		objmsg->set_toid(msg.objid());
		objmsg->set_recived(false);
		//插入数据库
		MsgDao::Insert(objmsg);
		delete objmsg;
		std::cout << "对方不在线" << std::endl;
		auto msgre = new Proto::Response_sendmsg();
		msgre->set_stat(true);
		msgre->set_msgid(1);
		response->set_allocated_response_sendmsg(msgre);
		p_con->send(response);
	}
	

}
