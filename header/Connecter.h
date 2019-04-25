#ifndef CONNECTER_H_TCUVAPLY
#define CONNECTER_H_TCUVAPLY

#include <memory>
#include <mutex>
#include <memory>
#include <cstring>
#include <queue>
#include <vector>
#include <pthread.h>

#include "Addresser.h"
#include "sockUtil.h"

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
		~Buffer () {
			delete[] buf;
		}

		size_t getSize() {
			return _end - _begin;
		}

		const char* getMsg() {
			return buf;
		}

		//向后移动指针
		void backPointer(size_t len);

	private:
		static const unsigned int MSGMAXSIZE = BUFSIZ * 2;
		size_t _begin;
		char * buf;
		size_t _end;
	};



	class Connecter
	{
	public:
		Connecter(int _sockfd) : 
			sockfd(_sockfd), connected(true),
			readBufend(0), writeBufHaveData(false)
		{
			::pthread_mutex_init(&mutex, nullptr);
		}

		virtual ~Connecter();

		virtual int recive(char* buf, size_t minLength = 0, size_t maxLength = BUFSIZ);
		virtual int send(const char* msg);
		virtual void closeThisConnecter();

		//可写回调函数， 若所有数据都写完则返回true， 反之返回false
		virtual bool onWriteable();

		virtual bool isConnected() {
			::pthread_mutex_lock(&mutex);
			bool stat = connected;
			::pthread_mutex_unlock(&mutex);
			return stat; 
		}
	
	protected:
		int sockfd;
		bool connected;
		size_t readBufend;
		bool writeBufHaveData;
		char readBuf[BUFSIZ*2];
		std::queue<Buffer> writeBuf;
		::pthread_mutex_t mutex;
	};

}

#endif /* end of include guard: CONNECTER_H_TCUVAPLY */
