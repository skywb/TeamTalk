#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/ip.h>
#include <sys/epoll.h>
#include <vector>

#define SERVER_PORT 12345


int main(int argc, char *argv[]) {

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1) std::cerr << "socket error" << std::endl;

	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(fd, (sockaddr*) &addr, sizeof(addr)) == -1)
		std::cerr << "bind error" << std::endl;

	if(listen(fd, 5) == -1) 
		std::cerr << "listen error" << std::endl;

	/*
	 * 创建epoll
	 * 参数已经被忽略， 只要是大于0的整数即可
	 */
	int rootfd = epoll_create(1);


	epoll_event tep;
	std::vector<epoll_event> epv;
	tep.events = EPOLLIN;
	tep.data.fd = fd;

	epoll_ctl(rootfd, EPOLL_CTL_ADD, fd, &tep);

	sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t len = sizeof(client_addr);
	bool done = false;

	while(!done) {/*{{{*/
		int cnt = epoll_wait(rootfd, &*epv.begin(), static_cast<int>(epv.size()), -1);

		if(static_cast<size_t>(cnt) == epv.size())
			epv.resize(epv.size() * 2);

		for (int i = 0; i < cnt; ++i) {
			if(epv[i].data.fd == fd) {

				int nfd = accept(fd, (sockaddr*)&client_addr, &len);
				tep.data.fd = nfd;
				tep.events = EPOLLIN;
				int ret = epoll_ctl(rootfd, EPOLL_CTL_ADD, nfd, &tep);
				if(ret == -1) {
					std::cerr << "epoll_ctl error" << std::endl;
					/* TODO: 监听失败 */
					continue;
					//break;
				}

				/* TODO: 使用工作线程处理新的连接 */

			} else {
				/* TODO: 有数据请求  调用工作线程处理*/

			}
		}
			
	}/*}}}*/

	return 0;
}
