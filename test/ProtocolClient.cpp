#include <iostream>

#include "IM/IMProtocol.h"
#include "util/sockUtil.h"

#include "util/testUtil.h"

int main()
{
	sockaddr_in addr;
	sockUtil::setNetClientAddr(&addr, "127.0.0.1", 9999);
	int fd = sockUtil::connectToAddr(&addr);
	sockUtil::setNoBlock(fd);

	auto login = std::make_shared<IM::LoginPdu> ();
	int id;
	while(true) {
		std::cout << "ID:" << std::endl;
		std::cin >> id;
		login->setUserId(id);
		std::cout << "password" << std::endl;
		char pwd[1000];
		std::cin >> pwd;
		login->setPassword(pwd);

		char buf[BUFSIZ];

		size_t len = IM::IMPduToSerivlization(buf, login);
		size_t cnt = 0;

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
		//printBity(buf, header.getHeaderLenth());
	}
	return 0;
}
