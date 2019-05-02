#include <iostream>

#include "IM/IMProtocol.h"
#include "util/sockUtil.h"

int main()
{
	std::cout << "ID:" << std::endl;
	IM::IMPduHeader::UserId id;
	cin >> id;
	std::cout << "cmd: 1.login, 2,logout, 3.sendmsg" << std::endl;
	int cid;
	cin >> cid;
	IM::IMPduHeader::CMD cmd;
	if(cid == 1) {
		cmd = IM::IMPduHeader::LOGIN;
	}
	else if(cid == 2) {
	   	cmd = IM::IMPduHeader::LOGOUT;
	}
	else {
		cmd = IM::IMPduHeader::SENDMSG;
	}

	IM::IMPduHeader header;
	header.setCommand(cmd);
	header.setUserId(id);
	header.setBodyLength(0);

	sockaddr_in addr;
	sockUtil::setNetClientAddr(&addr, "127.0.0.1", 9999);
	int fd = sockUtil::connectToAddr(&addr);

	char buf[BUFSIZ];
	write(fd, header.getHeader(buf), header.getHeaderLenth());
	
	return 0;
}
