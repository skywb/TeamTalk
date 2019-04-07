#include "Connecter.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>

namespace IM {

	bool Buffer::addMsg(const char* msg) {
		size_t len = strlen(msg);
		if(len > MSGMAXSIZE) {
			//log(msglength greate the MSGMAXSIZE)
			return false;
		}
		if(buf == nullptr) {
			_length = len;
			buf = new char[MSGMAXSIZE];
			::strncpy(buf, msg, _length);
		} else {
			if(_length + len > MSGMAXSIZE) {
				//log()
				return false;
			}
			::strncpy(buf+_length, msg, len);	
			_length += len;
		}
		return true;
	}


	Connecter::~Connecter() {
		close(_sockfd);
	}

	bool Connecter::send(char* msg) {
		std::lock_guard<std::mutex> lock(_mutex);
		int len = strlen(msg);
		int re = write(_sockfd, msg, len);

		if(re == -1) {
			//log(write eror)
			return false;
		}
		else if(re < len) {
			_bufque.push_back(Buffer(msg+re));
			/* TODO: 添加可写事件 */
			return true;
		}

		return true;
	}
	int Connecter::recive(char* buf) {
		std::lock_guard<std::mutex> lock(_mutex);

		int n =  read(_sockfd, buf, BUFSIZ);
		if(n == 0) connected = false;
		return n;
	}
}
