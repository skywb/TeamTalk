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

	/*
	 * 数据缓冲区， 可以暂存数据
	 */

	class Buffer
	{
	public:
		Buffer () :  _begin(0), buf(nullptr), _end(0) {}
		Buffer (const char* str) {
			_end = strlen(str);
			if(_end > MSGMAXSIZE) {
				//log(error);
				buf = nullptr;
			} else {
				buf = new char[MSGMAXSIZE];
				::strncpy(buf, str, _end);
			}
		}
		virtual ~Buffer () {
			delete[] buf;
		}

		size_t getSize() {
			return _end - _begin;
		}

		//向后移动指针
		void backPointer(size_t len);

		//bool addMsg(const char* msg);
		//const char* c_str() {
		//	return buf;
		//}
	
	private:
		static const unsigned int MSGMAXSIZE = BUFSIZ;
		size_t _begin;
		char * buf;
		size_t _end;
	};



	class Connecter
	{
	public:
		Connecter(int sockfd) : _sockfd(sockfd), connected(true) {
		}

		virtual ~Connecter();

		virtual int send(char* msg);
		virtual int recive(char* buf);

		virtual void onWriteable();
		virtual void onReadable();

		virtual bool isConnected() {
			std::lock_guard<std::mutex> lock(_mutex);
			return connected; 
		}
	
	protected:
		int _sockfd;
		std::queue<Buffer> _readBuf;
		std::queue<Buffer> _writeBuf;
		std::mutex _mutex;
		bool connected;
	};

	class TCPConnecter : public Connecter
	{
	public:
		TCPConnecter(int sockfd) :Connecter(sockfd){ }

		~TCPConnecter () {}
	
	};


}

#endif /* end of include guard: CONNECTER_H_TCUVAPLY */
