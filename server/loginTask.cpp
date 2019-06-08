#include "reactor/IMReactor.h"
#include "IM/User.h"
#include "loginTask.h"
#include "dao/UserDao.h"

ConnMap* ConnMap::object_p = new ConnMap();



std::shared_ptr<IM::IMConn> ConnMap::find(int fd) {
	std::lock_guard<std::mutex> lock(m_mutex);
	auto p = m_map.find(fd);
	if(p == m_map.end()) return nullptr;
	else return p->second.lock();
}

std::pair<bool, std::shared_ptr<IM::IMConn>> ConnMap::add(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p) {
	std::lock_guard<std::mutex> lock(m_mutex);
	auto it = m_map.insert(p);
	if(it.second) {
		return std::pair<bool, std::shared_ptr<IM::IMConn>> (true, (it.first)->second.lock());
	} else {
		m_map[p.first] = std::weak_ptr<IM::IMConn> (p.second);
		return std::pair<bool, std::shared_ptr<IM::IMConn>> (false, it.first->second.lock());
	}
}

bool ConnMap::del(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p) {
	std::lock_guard<std::mutex> lock(m_mutex);
	auto it = m_map.find(p.first);
	if(it == m_map.end()) return false;
	m_map.erase(it);
	return true;
}

void LoginTask::doit() {
	auto login = request->request_login();
	User user;
	user.setId(login.id());
	user.setPassword(login.password());
	response =  new  Proto::Response();
	auto re =  new Proto::Response_login();
	auto userConn = ConnMap::findConnecterById(user.getId());
	if(userConn != nullptr) {
		#ifdef NDEBUG
			std::cout << "账号已在线" << std::endl;
		#endif
		re->set_stat(Proto::Response_login_STAT_ERROR);
		return ;
	}

	User* dbUser = UserDao::Obtain(user.getId());

	//账号不存在
	if(dbUser == nullptr) {
		re->set_stat(Proto::Response_login_STAT_ACCOUNT_NULL);
		return ;
	}
	//登录成功
	if(user.getPassword() == dbUser->getPassword()) {

		re->set_stat(Proto::Response_login_STAT_SUCCESS);
		re->set_friends(dbUser->getFriends());
		ConnMap::addAccount(std::make_pair(user.getId(), p_con));

	} else { //密码错误
		re->set_stat(Proto::Response_login_STAT_PASSWORD_ERROR);
   	}
	response->set_type(Proto::Response_Type_LOGIN);
	response->set_allocated_response_login(re);
	//auto con  = ConnMap::findConnecterById(login.id());
	p_con->send(response);
}


void GetFriendInfoTask::doit() {
	response = new  Proto::Response();
	auto cmd = request->request_friendinfo();
	User::Account id  = cmd.friendid();
	auto  user = UserDao::Obtain(id);
	if(user == nullptr) {
		/* TODO: 没有找到 <29-05-19, sky> */
		std::cout << "没有找到" << std::endl;
		return;
	}
	auto re = new  Proto::Response_FriendInfo();
	re->set_id(user->getId());
	auto info =  new Proto::AccountINFO();
	info->set_name(user->getName());
	info->set_id(user->getId());
	re->set_allocated_info(info);
	response->set_type(Proto::Response_Type_FriendInfo);
	response->set_allocated_response_friendinfo(re);
	auto con = ConnMap::findConnecterById(cmd.fromid());
	if(con)
	{
		con->send(response);
		//std::cout << "发送成功" << std::endl;
	} else   {
		//std::cout << "发送失败" << std::endl;
	}
	delete response;
}






