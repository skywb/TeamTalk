#ifndef CONNECTER_H_TCUVAPLY
#define CONNECTER_H_TCUVAPLY

#include "Addresser.h"
#include "sockUtil.h"
#include <memory>
#include <mutex>
#include <memory>
#include <cstring>
#include <queue>
#include <vector>

namespace IM {

	class Buffer
	{
	public:
		Buffer () : buf(nullptr), _length(0) {}
		Buffer (const char* str) {
			_length = strlen(str);
			if(_length > MSGMAXSIZE) {
				//log(error);
				buf = nullptr;
			} else {
				buf = new char[MSGMAXSIZE];
				::strncpy(buf, str, _length);
			}
		}
		virtual ~Buffer () {
			delete[] buf;
		}

		size_t getSize() {
			return _length;
		}

		bool addMsg(const char* msg);
		const char* c_str() {
			return buf;
		}
	
	private:
		static const unsigned int MSGMAXSIZE = BUFSIZ;
		char * buf;
		size_t _length;
	};



	class Connecter
	{
	public:
		Connecter(int sockfd) : _sockfd(sockfd), connected(true) {

		}
		virtual ~Connecter();

		virtual bool send(char* msg);
		virtual bool send();

		virtual int recive(char* buf);
		virtual bool isConnected() {
			std::lock_guard<std::mutex> lock(_mutex);
			return connected; 
		}
	
	protected:
		int _sockfd;
		std::queue<Buffer> _bufque;
		std::mutex _mutex;
		bool connected;
	};


}

#endif /* end of include guard: CONNECTER_H_TCUVAPLY */
