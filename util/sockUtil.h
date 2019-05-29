#ifndef SOCKUTIL_H_YLIRQ09U
#define SOCKUTIL_H_YLIRQ09U

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace sockUtil {
	
	//获取一个socket， 并绑定到addr上， 并listen此套接字， 返回此套接字
	//错误返回-1
	int listenToAddr(const sockaddr_in* addr, const int num);
	int listenToAddr(const sockaddr_un* addr, const int num);

	//返回一个连接到addr的套接字
	int connectToAddr(const sockaddr_in* addr);
	int connectToAddr(const sockaddr_un* addr);
	
	bool setUnixAddr(sockaddr_un* addr);
	bool setUnixAddr(sockaddr_un* addr, const char *_path);
	bool setNetServerAddr(sockaddr_in* addr, const uint16_t port);
	bool setNetServerAddr(sockaddr_in* addr,const char*IP, const uint16_t port);
	int setNetClientAddr(sockaddr_in* addr, const char* IP, const uint16_t port);

	int acceptNewConnect(int fd);
	int setNoBlock(int fd);
}


#endif /* end of include guard: SOCKUTIL_H_YLIRQ09U */
