#include "Addresser.h"
#include "util/sockUtil.h"

namespace  BlueCat {

NetAddresser::NetAddresser (const char* IP, const uint16_t port) {
	if(IP == nullptr) sockUtil::setNetServerAddr(&addr, port);
	else sockUtil::setNetServerAddr(&addr, IP, port);
}
NetAddresser::~NetAddresser () {

}

sockaddr* NetAddresser::getSockaddr() {
	return (sockaddr*)&addr;
}


UnixAddresser::UnixAddresser () {
	::memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	sockUtil::setUnixAddr(&addr);
}
UnixAddresser::UnixAddresser (const char* _path) {
	sockUtil::setUnixAddr(&addr, _path);
}
UnixAddresser::~UnixAddresser () {

}
sockaddr* UnixAddresser::getSockaddr() {
	return (sockaddr*)&addr;
}


}
