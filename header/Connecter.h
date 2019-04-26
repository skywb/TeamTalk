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
			sockfd(_sockfd), connected(true), readBufbeg(0),
			readBufend(0), writeBufHaveData(false), readBufMaxLenth(BUFSIZ*2)
		{
			readBuf = (char*)::malloc(BUFSIZ*2);
			::pthread_mutex_init(&mutex, nullptr);
		}

		virtual ~Connecter() {
			::free(readBuf);
			::close(sockfd);
		}

		//读取数据
		virtual int recive(char* buf, size_t minLength = 0);
		/*
		 * 尝试读取
		 * 若数据不符合要求，通过rollback_tryRecive()使数据回到缓冲区，变为未读状态
		 * 若符合要求，调用commit_tryRecive()提交已读取内容
		 */
		virtual bool startTryRecive(size_t minLength = 0, size_t maxLength = BUFSIZ);
		virtual int tryRecive(char* buf, size_t length = 0);
		//确认读取内容
		virtual bool commit_tryRecive();
		//回滚数据，使tryRecive读取的数据回到缓冲区中
		virtual bool rollback_tryRecive();
		//发送数据
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
		size_t readBufbeg;
		size_t readBufend;
		bool writeBufHaveData;
		size_t readBufMaxLenth;
		char* readBuf;
		std::queue<Buffer> writeBuf;
		::pthread_mutex_t mutex;
	};

}

#endif /* end of include guard: CONNECTER_H_TCUVAPLY */
