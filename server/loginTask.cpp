#include "reactor/IMReactor.h"
#include "IM/User.h"
#include "loginTask.h"
#include "dao/UserDao.h"

ConnMap* ConnMap::object_p = new ConnMap();



std::shared_ptr<IM::IMConn> ConnMap::find(int fd) {
	std::lock_guard<std::mutex> lock(m_mutex);
	auto p = m_map.find(fd);
	if(p == m_map.end()) return nullptr;
	else return p->second;
}

std::pair<bool, std::shared_ptr<IM::IMConn>> ConnMap::add(std::pair<User::Account, std::shared_ptr<IM::IMConn>> p) {
	std::lock_guard<std::mutex> lock(m_mutex);
	auto it = m_map.insert(p);
	if(it.second) {
		return std::pair<bool, std::shared_ptr<IM::IMConn>> (true, (it.first)->second);
		
	} else {
		m_map[p.first] = p.second;
		return std::pair<bool, std::shared_ptr<IM::IMConn>> (false, nullptr);
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
	User user;
	user.setId(request.id());
	user.setPassword(request.password());


	auto userConn = ConnMap::findConnecterById(user.getId());
	if(userConn != nullptr) {
		response.set_stat(Proto::Response_login_STAT_ERROR);
		return ;
	}

	User* dbUser = UserDao::Obtain(user.getId());

	//账号不存在
	if(dbUser == nullptr) {
		response.set_stat(Proto::Response_login_STAT_ACCOUNT_NULL);
		return ;
	}
	//登录成功
	if(user.getPassword() == dbUser->getPassword()) {

		response.set_stat(Proto::Response_login_STAT_SUCCESS);
		response.set_friends(dbUser->getFriends());
		//ConnMap::addAccount(std::make_pair(user.getId(), p_con));

	} else { //密码错误
		response.set_stat(Proto::Response_login_STAT_PASSWORD_ERROR);
   	}

}
