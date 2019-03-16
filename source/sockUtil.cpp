#include "sockUtil.h"
#include <iostream>
#include <sys/un.h>


int sockUtil::listenToAddr(const sockaddr* addr, const int num) {
	int fd = socket(addr->sa_family, SOCK_STREAM, 0);
	if(bind(fd, addr, sizeof(addr) == -1)) {
		close(fd);
		//Log("bind error to addr");
		std::cout << "bind error to addr" << std::endl;
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


int sockUtil::connectToAddr(const sockaddr* addr) {
	int fd = socket(addr->sa_family, SOCK_STREAM, 0);
	if(connect(fd, addr, sizeof(addr)) == -1) {
		close(fd);
		//Log("connect error");
		std::cout << "connect error" << std::endl;
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

bool sockUtil::setNetAddr(sockaddr_in* addr, uint16_t port) {
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = htonl(INADDR_ANY);
	return true;

}

bool sockUtil::setNetAddr(sockaddr_in* addr, uint32_t IP, uint16_t port) {
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = htonl(IP);
	return true;
}



