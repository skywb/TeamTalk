#include <iostream>
#include <sys/un.h>
#include <fcntl.h>

#include "sockUtil.h"

int sockUtil::listenToAddr(const sockaddr_in* addr, const int num) {
	int fd = socket(addr->sin_family, SOCK_STREAM, 0);
	if(bind(fd, (sockaddr*)addr, sizeof(sockaddr_in)) == -1) {
		close(fd);
		//Log("bind error to addr");
		std::cout << "bind error to addr" << std::endl;
		std::cout << strerror(errno) << std::endl;
		return -1;
	}
	if(listen(fd, num) == -1) {
		close(fd);
		//Log("listen error");
		std::cout << "listen error" << std::endl;
		return -1;
	}

	return fd;
}

int sockUtil::listenToAddr(const sockaddr_un* addr, const int num) {
	int fd = socket(addr->sun_family, SOCK_STREAM, 0);
	if(bind(fd, (sockaddr*)addr, sizeof(sockaddr_un)) == -1) {
		close(fd);
		//Log("bind error to addr");
		std::cout << "bind error to addr" << std::endl;
		std::cout << strerror(errno) << std::endl;
		return -1;
	}
	if(listen(fd, num) == -1) {
		close(fd);
		//Log("listen error");
		std::cout << "listen error" << std::endl;
		std::cout << strerror(errno) << std::endl;
		return -1;
	}

	return fd;
}

int sockUtil::connectToAddr(const sockaddr_in* addr) {
	int fd = socket(addr->sin_family, SOCK_STREAM, 0);
	if(connect(fd, (sockaddr*)addr, sizeof(sockaddr_in)) == -1) {
		close(fd);
		//Log("connect error");
		std::cout << "connect error" << std::endl;
		std::cout << strerror(errno) << std::endl;
		return -1;
	}
	return fd;
}

int sockUtil::connectToAddr(const sockaddr_un* addr) {
	int fd = socket(addr->sun_family, SOCK_STREAM, 0);
	if(connect(fd, (sockaddr*)addr, sizeof(sockaddr_un)) == -1) {
		close(fd);
		//Log("connect error");
		std::cout << "connect error" << std::endl;
		std::cout << strerror(errno) << std::endl;
		return -1;
	}
	return fd;
}


bool sockUtil::setUnixAddr(sockaddr_un* addr) {
	memset(addr, 0, sizeof(sockaddr_un));
	return true;
}

bool sockUtil::setUnixAddr(sockaddr_un* addr, const char* _path) {

	memset(addr, 0, sizeof(sockaddr_un));
	addr->sun_family = AF_UNIX;
	strcpy(addr->sun_path, _path);

	return true;
}

bool sockUtil::setNetServerAddr(sockaddr_in* addr, const uint16_t port) {
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = htonl(INADDR_ANY);
	return true;

}

bool sockUtil::setNetServerAddr(sockaddr_in* addr, const char* IP, const uint16_t port) {
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	//addr->sin_addr.s_addr = htonl(INADDR_ANY);
	addr->sin_addr.s_addr = inet_addr(IP);
	return true;

}

int sockUtil::setNetClientAddr(sockaddr_in* addr, const char* IP, const uint16_t port) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	//addr->sin_addr.s_addr = htonl(IP);
	addr->sin_addr.s_addr = inet_addr(IP);
	return fd;
}

int acceptNewConnect(int fd) {
	
	//接受新的连接
	//加入EPOLL监听树中
	//ET模式
	sockaddr_in addr;
	socklen_t len;
	len = sizeof(addr);
	int nfd = accept(fd, (sockaddr*)&addr, &len);
	return nfd;
}

int setNoBlock(int fd) {
	int flags = ::fcntl(fd, F_GETFL);
	::fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	return flags;

}



