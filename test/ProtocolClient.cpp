#include <iostream>

#include "IM/IMProtocol.h"
#include "util/sockUtil.h"

#include "util/testUtil.h"

int main()
{
	sockaddr_in addr;
	sockUtil::setNetClientAddr(&addr, "127.0.0.1", 9999);
	int fd = sockUtil::connectToAddr(&addr);

	IM::IMPduHeader header;
	while(true) {
		std::cout << "ID:" << std::endl;
		IM::IMPduHeader::UserId id;
		cin >> id;
		std::cout << "cmd: 1.login, 2,logout, 3.sendmsg" << std::endl;
		int cid;
		cin >> cid;
		IM::IMPduHeader::CMD cmd;
		if(cid == 1) {
			cmd = IM::IMPduHeader::LOGIN;
			header.setCommand(cmd);
			header.setUserId(id);
			header.setBodyLength(0);
		}
		else if(cid == 2) {
			cmd = IM::IMPduHeader::LOGOUT;
			header.setCommand(cmd);
			header.setUserId(id);
		} else {
			cmd = IM::IMPduHeader::SENDMSG;
			header.setCommand(cmd);
			header.setUserId(id);
			header.setObjUserId(111);
			header.setBodyLength(0);
		}



		char buf[BUFSIZ];
		header.getHeader(buf);
		sockUtil::setNoBlock(fd);

		int len = header.getHeaderLenth();
		int cnt = 0;

		std::cout << "header len = " << len << std::endl;

		int re = 0;
		while(cnt < len) {
			re = write(fd, buf+cnt, len-cnt);
			cnt += re;
			if(re < 0) 
			{
				std::cout << strerror(errno)<< std::endl;
			}
		}

		std::cout << re << std::endl;
		printBity(buf, header.getHeaderLenth());


	}
	return 0;
}
