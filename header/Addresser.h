#ifndef ADDRESSER_H_XPCHAIJF
#define ADDRESSER_H_XPCHAIJF

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

namespace BlueCat {

class Addresser
{
public:
	Addresser ();
	virtual ~Addresser ();

	virtual sockaddr* getSockaddr() = 0;
	virtual socklen_t getAddressLenth() = 0;
//	virtual uint16_t getPort() = 0;
//	virtual uint32_t getIp() = 0;
};


/*
 * 网络连接地址
 */
class NetAddresser : public Addresser
{
public:
	NetAddresser () {
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
	}
	NetAddresser (const char* IP, const uint16_t port);
	virtual ~NetAddresser ();

	sockaddr* getSockaddr() override;
	socklen_t getAddressLenth() override { return sizeof(sockaddr_in); }

	void setIP(const char* IP) {
		addr.sin_addr.s_addr = inet_addr(IP);
	}
	void setPort(uint16_t port) {
		addr.sin_port = htons(port);
	}

private:
	sockaddr_in addr;
};



/*
 * 本地连接地址
 */
class UnixAddresser : public Addresser
{
public:
	UnixAddresser () {
		::memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
	}
	UnixAddresser (const char* _path);
	virtual ~UnixAddresser ();

	sockaddr* getSockaddr() override;
	socklen_t getAddressLenth() override { return sizeof(sockaddr_un); }

	void setPath(const char* _path) {
		strcpy(addr.sun_path, _path);
	}

private:
	sockaddr_un addr;
};





}


#endif /* end of include guard: ADDRESSER_H_XPCHAIJF
 */
