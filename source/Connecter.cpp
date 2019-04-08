#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>

#include "Connecter.h"
#include "IMReactor.h"

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
			_bufque.push(Buffer(msg+re));
			/* TODO: 添加可写事件 */
			return true;
		}

		return true;
	}

	/*
	 * 套接字可写
	 * 将缓冲区内的内容写入
	 * 如果缓冲区中的内容全部发送返回true
	 * 否则返回false
	 */
	bool Connecter::send() {
		while(!_bufque.empty())
		{

			auto& buf = _bufque.front();
			int n = write(_sockfd, buf.c_str(), buf.getSize());
			if(n < buf.getSize()) 
			{
				/* TODO: 当前缓冲区发送了n个字节， 应减去前n个字符 */
				break;
			}
			else _bufque.pop();
		}
		return _bufque.empty();
	}

	int Connecter::recive(char* buf) {
		std::lock_guard<std::mutex> lock(_mutex);

		int n =  read(_sockfd, buf, BUFSIZ);
		if(n == 0) connected = false;
		return n;
	}
}
