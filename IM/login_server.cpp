#include "login_server.h"
#include "dao/UserDao.h"

ConnMap* ConnMap::object_p = new ConnMap();
//ConnMap* ConnMap::object_p = nullptr;



std::shared_ptr<IM::Connecter> ConnMap::find(int fd) {
	pthread_mutex_lock(&m_mutex);
	auto it = m_map.find(fd);
	pthread_mutex_unlock(&m_mutex);
	if(it == m_map.end()) {
		return nullptr;
	} else {
		return it->second;
	}
}
std::shared_ptr<IM::Connecter> ConnMap::add(std::pair<User::Account, std::shared_ptr<IM::Connecter>> p) {
	auto res = find(p.first);
	::pthread_mutex_lock(&m_mutex);
	if(res == nullptr)
	{
		m_map.insert(p);
		res = p.second;
	}
	::pthread_mutex_unlock(&m_mutex);
	return res;
}

bool ConnMap::del(std::pair<User::Account, std::shared_ptr<IM::Connecter>> p) {
	auto it = m_map.find(p.first);
	pthread_mutex_lock(&m_mutex);
	if(it == m_map.end())
	{
		pthread_mutex_unlock(&m_mutex);
		return false;
	}
	else {
		m_map.erase(it);
	}
	pthread_mutex_unlock(&m_mutex);
	return true;
}

void login_server(std::shared_ptr<IM::LoginPdu> pdu, std::shared_ptr<IM::Connecter> p_con) {
	
	User user;
	user.setId(pdu->getUserId());
	user.setPassword(pdu->getPassword());


	auto userConn = ConnMap::findConnecterById(user.getId());
	if(userConn != nullptr) {
		std::cout << "用户已在线" << std::endl;
		return ;
	}

	User* dbUser = UserDao::Obtain(user.getId());

	//账号不存在
	if(dbUser == nullptr) {
		std::cout << "账号不存在" << std::endl;
	}
	//登录成功
	if(user.getPassword() == dbUser->getPassword()) {

		std::cout << "登录成功" << std::endl;
		ConnMap::addAccount(std::make_pair(user.getId(), p_con));

	} else { //密码错误

		std::cout << "密码错误" << std::endl;
   	}

	/* TODO: 
	 * 从数据库获取user信息
	 * 对比密码
	 * 登录成功则插入sockmap中
	 * 否则返回错误信息
	 * <08-05-19, sky> */
}








