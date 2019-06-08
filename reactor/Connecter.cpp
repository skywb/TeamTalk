#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <exception>

#include "reactor/Connecter.h"
#include "reactor/IMReactor.h"
#include "util/Log.h"


using namespace IM;

void Buffer::backPointer(size_t len) {
	//NOTE: 此处应该抛出异常
	if(_end + len >= MSGMAXSIZE) return;
	
	_end += len;
}



int Connecter::recive(char* buf, size_t length) {

	std::lock_guard<std::mutex> lock(m_mutex);

	if(readable == false) 
	{
		return 0;
	}


	////若readBufbeg不为0 则之前调用了tryRecive未commit或未rollback
	//assert(readBufbeg == 0);

	/* NOTE:
	 * 如果length大于BUFSIZ, 并且maxLength大于length
	 * 此时应该可以直接读到buf中
	 * 这部分尚未写
	 * */

	if(length > BUFSIZ)
	{
		return -1;
	}

	//缓冲区内的数据足够
	if(readBufend >= length) {
		::strncpy(buf, readBuf, length);
		::strncpy(readBuf, readBuf+length, readBufend-length);
		readBufend -= length;
		return length;
	}

	int re = ::read(sockfd, readBuf+readBufend, length);
	if(re == 0) 
	{
		/* TODO: 
		 * 从mp中删除该连接
		 * <26-04-19, yourname> */
		//std::cout << "断开连接" << std::endl;
		//IM::IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLIN, sockfd));
		closeThisConnecter();
		return 0;
	}
	if(re == -1) {
		//没有信息可以读
		if(errno == EAGAIN)
		{
			return 0;
		} else {
			Log::log(Log::ERROR, "read error in Connecter recive");
		}

	} else {
		readBufend += re;
	}

	//缓冲区数据加上读到的数据足够length
	if(readBufend >= length) {
		::strncpy(buf, readBuf, length);
		::strncpy(readBuf, readBuf+length, readBufend-length);
		readBufend -= length;
		return length;
	}
	//不足最小长度
	return 0;

}


int Connecter::send(const char* msg, size_t len) {

	if(false == isConnected()) return -1;

	std::lock_guard<std::mutex> lock(m_mutex);
	int re = 0;

	if(writeBufHaveData) {
		writeBuf.push(Buffer(msg, len));
	} else {
		int re = write(sockfd, msg, len);
		if(re == -1) {
			Log::log(Log::ERROR, "write error");
		}

		if(static_cast<size_t>(re) < len) {
			writeBuf.push(Buffer(msg+re, len-re));
			writeBufHaveData = true;
			IMReactor::optEventListen(Event(EPOLL_CTL_ADD, EPOLLOUT, sockfd));
		}
	}

	return re;
}

void Connecter::readToBuffer() {
	if(readBufend - readBufbeg < readBufMaxLenth/2 && readBufbeg > readBufbeg/3) {
		memcpy(readBuf, readBuf+readBufbeg, readBufend-readBufbeg);
	}
	int re = ::read(sockfd, readBuf+readBufend, readBufMaxLenth-readBufend);
	if(re == 0) 
	{
		/* TODO: 
		 * 从mp中删除该连接
		 * <26-04-19, yourname> */
		//std::cout << "断开连接" << std::endl;
		//IM::IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLIN, sockfd));
		closeThisConnecter();
		return ;
	}
	if(re == -1) {
		//没有信息可以读
		if(errno == EAGAIN)
		{
			return ;
		} else {
			Log::log(Log::ERROR, "read error in Connecter recive");
		}

	} else {
		readBufend += re;
	}
}


void Connecter::closeThisConnecter() {

	char buf[100];
	sprintf(buf, "%d断开连接", sockfd);
	Log::log(Log::DEBUG, buf);
	if(readable || writeable) {
		readable = false;
		writeable = false;
		IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLIN, sockfd));
	}
	return ;
}


bool Connecter::onWriteable() {

	for(auto& cur = writeBuf.front(); !writeBuf.empty(); writeBuf.pop()) {
		int re = ::write(sockfd, cur.getMsg(), cur.getSize());
		if(re == 0) 
		{
			IM::IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLOUT, sockfd));
			if(false == isConnected()) {
				auto reactor = IM::IMReactor::getInstances();
				reactor->delConnecter(sockfd);
			}
			return false;
		}
		if(re == -1) {
			char msg[BUFSIZ];
			sprintf(msg, "write to socket error, errno : %s\n", ::strerror(errno));
			Log::log(Log::ERROR, msg);

		}
		if(static_cast<size_t>(re) < cur.getSize()) {
			cur.backPointer(re);
			return false;
		}
		
	}
	return true;
}



bool IMConn::send(Proto::Response *response) {
	if(!response->IsInitialized()) {
		return false;
	}

	int len = response->ByteSize();
	char buf[BUFSIZ];
	memcpy(buf, &len, sizeof(len));
	int ok = response->SerializeToArray(buf+sizeof(len), BUFSIZ-sizeof(len));
	if(ok) {
		Connecter::send(buf, len+sizeof(len));
	}	
	return ok;
}


Proto::Request* IMConn::recive() {

	std::cout << "IMConn recive" << std::endl;
	if(readable == false) 
	{
		return nullptr;
	}

	int len;

	if(readBufend - readBufbeg < sizeof(len) ) {
		readToBuffer();
	}
	if(readBufend - readBufbeg < sizeof(len) ) {
		return nullptr;
	}
	len = *(int*)(readBuf+readBufbeg);

	if(readBufend - readBufbeg < len) {
		if(readBufMaxLenth - readBufbeg < len)  {
			Log::log(Log::ERROR, "Connecter readBuffer less than Protocol");
			return nullptr;
		}
		readToBuffer();
	}
	if(readBufend - readBufbeg < len) {
		return nullptr;
	}

	Proto::Request *request = new Proto::Request();
	bool ok = request->ParseFromArray(readBuf+readBufbeg+sizeof(len), len);
	if(!ok) {
		delete  request;
		return nullptr;
	}
	readBufbeg += sizeof(len) + len;
	//不足最小长度
	return request;

}

ClientConn::ClientConn(const char* IP, const uint16_t port): Connecter(0) {
	sockaddr_in addr;
	sockUtil::setNetClientAddr(&addr,IP, port);
	sockfd = sockUtil::connectToAddr(&addr);
	sockUtil::setNoBlock(sockfd);
	if(sockfd < 0) {
		readable = false;
		writeable = false;
	}
	else {
		readable = true;
		writeable = true;
	}
}

bool send(Proto::Request* request);
Proto::Response* recive();


bool ClientConn::send(Proto::Request *request) {
	if(!request->IsInitialized()) {
		return false;
	}

	int len = request->ByteSize();
	char buf[BUFSIZ];
	memcpy(buf, &len, sizeof(len));
	std::cout << len << std::endl;
	int ok = request->SerializeToArray(buf+sizeof(len), BUFSIZ-sizeof(len));
	if(ok) {
		Connecter::send(buf, len+sizeof(len));
	}	
	return ok;
}


Proto::Response* ClientConn::recive() {

	if(readable == false) 
	{
		return nullptr;
	}

	int len;
	if(readBufend - readBufbeg < sizeof(int) ) {
		readToBuffer();
	}

	if(readBufend - readBufbeg < sizeof(int) ) return nullptr;

	len = *(int*)(readBuf+readBufbeg);
	if(len < 0) {
		Log::log(Log::ERROR, "协议错误， len小于0");
		return nullptr;
	}
	if(readBufend - readBufbeg < static_cast<unsigned int>(len)) {
		readToBuffer();
	}

	if(readBufend - readBufbeg < static_cast<unsigned int>(len)) { return nullptr; }

	Proto::Response *response = new Proto::Response();
	bool ok = response->ParseFromArray(readBuf+readBufbeg+sizeof(int), len);
	if(!ok) {
		delete  response;
		return nullptr;
	}
	readBufbeg += sizeof(len) + len;

	//不足最小长度
	return response;

}


void ClientConn::waitMsg() {
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);
	int cnt = select(sockfd+1, &fds, NULL, NULL, NULL);
	if (cnt != 1) {
		std::cout << "error" << std::endl;	
	}
	return;
}
