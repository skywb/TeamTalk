#include "login_server.h"
#include "dao/UserDao.h"

SockMap* SockMap::object_p = new SockMap();
//SockMap* SockMap::object_p = nullptr;



int SockMap::findId(int fd) {
	pthread_mutex_lock(&m_mutex);
	auto it = m_map.find(fd);
	pthread_mutex_unlock(&m_mutex);
	return (it == m_map.end()) ? -1 : it->second;

}
bool SockMap::add(std::pair<User::Account, int> p) {
	pthread_mutex_lock(&m_mutex);
	auto ret =  m_map.insert(p);
	pthread_mutex_unlock(&m_mutex);
	return ret.second;	
}

bool SockMap::del(std::pair<User::Account, int> p) {
	pthread_mutex_lock(&m_mutex);
	auto it = m_map.find(p.first);
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

void login_server(std::shared_ptr<IM::LoginPdu> pdu) {
	
	User user;
	user.setId(pdu->getUserId());
	user.setPassword(pdu->getPassword());


	/* TODO: 
	 * 从数据库获取user信息
	 * 对比密码
	 * 登录成功则插入sockmap中
	 * 否则返回错误信息
	 * <08-05-19, sky> */

}








