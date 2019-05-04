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

	::pthread_mutex_lock(&mutex);

	if(readable == false) 
	{
		::pthread_mutex_unlock(&mutex);
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
		pthread_mutex_unlock(&mutex);
		return -1;
	}

	//缓冲区内的数据足够
	if(readBufend >= length) {
		::strncpy(buf, readBuf, length);
		::strncpy(readBuf, readBuf+length, readBufend-length);
		readBufend -= length;
		pthread_mutex_unlock(&mutex);
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
		pthread_mutex_unlock(&mutex);
		return 0;
	}
	if(re == -1) {
		//没有信息可以读
		if(errno == EAGAIN)
		{
			pthread_mutex_unlock(&mutex);
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
		pthread_mutex_unlock(&mutex);
		return length;
	}

	pthread_mutex_unlock(&mutex);
	//不足最小长度
	return 0;

}

bool Connecter::startTryRecive(size_t minLength, size_t maxLength) {

	if(false == isConnected()) {
		return false;
	}

	::pthread_mutex_lock(&mutex);

	if(TryReciving == true) {
		::pthread_mutex_unlock(&mutex);
		throw TryReciveException("TryReciving has started");
	}

	TryReciving = true;
	readBufbeg = 0;
	if(maxLength >= readBufMaxLenth) {
		if(nullptr == ::realloc(readBuf, maxLength+10)) {
			char msg[200];
			::sprintf(msg, "realloc failed in tryRecive: maxLength = %d", static_cast<int>(maxLength));
			
			Log::log(Log::WARNING, msg);
			return false;
		}
	}
	return true;
}

int Connecter::tryRecive(char* buf, size_t length) {

	if(TryReciving == false) {
		throw TryReciveException("TryReciving has not started");
	}

	//当前已经加锁，不需要调用isConnected方法， 也不能调用， 否则死锁
	if(true != readable) {
		return -1;
	}

	if(readBufend - readBufbeg >= length) {
		::memcpy(buf, readBuf+readBufbeg, length);
		readBufbeg += length;
		return length;
	}

	int re = ::read(sockfd, readBuf+readBufend, readBufMaxLenth-readBufend);
	if(re == 0) 
	{
		/* TODO: 
		 * 从mp中删除该连接
		 * <26-04-19, sky> */
		//std::cout << "close" << std::endl;
		closeThisConnecter();
		return 0;
		//std::cout << "断开连接" << std::endl;
	}
	else if(re == -1) {
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
	if(readBufend-readBufbeg >= length) {
		::memcpy(buf, readBuf+readBufbeg, length);
		readBufbeg += length;
		return length;
	}
	return 0;
}


bool Connecter::commit_tryRecive() {

	if(TryReciving == false) {
		throw TryReciveException("TryReciving has not started");
	}
	TryReciving = false;
	size_t len = readBufend - readBufbeg;
	::strncpy(readBuf, readBuf+readBufbeg, len);
	readBufend -= readBufbeg;
	readBufbeg = 0;
	::pthread_mutex_unlock(&mutex);
	return true;
}
bool Connecter::rollback_tryRecive() {
	if(TryReciving == false) {
		throw TryReciveException("TryReciving has not started");
	}
	TryReciving = false;
	readBufbeg = 0;
	::pthread_mutex_unlock(&mutex);
	return true;
}


int Connecter::send(const char* msg) {

	if(false == isConnected()) return -1;

	::pthread_mutex_lock(&mutex);
	int re = 0;

	if(writeBufHaveData) {
		writeBuf.push(Buffer(msg));
	} else {
		int len = strlen(msg);
		int re = write(sockfd, msg, len);
		if(re < len) {
			writeBuf.push(Buffer(msg+re));
			writeBufHaveData = true;
			IMReactor::optEventListen(Event(EPOLL_CTL_ADD, EPOLLOUT, sockfd));
		}
	}

	pthread_mutex_unlock(&mutex);
	return re;
}

void Connecter::closeThisConnecter() {

	char buf[100];
	sprintf(buf, "%d断开连接", sockfd);
	Log::log(Log::DEBUG, buf);
	if(readable || writeable) {
		readable = false;
		writeable = false;
		IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLIN, sockfd));

//		if(readable) {
//			readable = false;
//			IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLIN, sockfd));
//		}
//		if(writeable || writeBufHaveData) {
//			writeable = false;
//			writeBufHaveData = false;
//			IMReactor::optEventListen(Event(EPOLL_CTL_DEL, EPOLLOUT, sockfd));
//			while(!writeBuf.empty()) {
//				writeBuf.pop();
//			}
//		}
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
