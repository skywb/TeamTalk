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
#include "util/sockUtil.h"

namespace IM {

	/* 数据缓冲区， 可以暂存数据
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

	class TryReciveException : public std::exception
	{
	public:
		TryReciveException (const char* msg) :msg(msg) {}
		virtual ~TryReciveException () {}

		const char* what() const throw() {
			return msg;
		}
	
	private:
		const char* msg;
	};


	class Connecter
	{
	public:
		Connecter(int _sockfd) : 
			sockfd(_sockfd), connected(true), TryReciving(false), readBufbeg(0),
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

		/* 尝试读取
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
		//正在连接的socket
		int sockfd;
		//是否是一个可用的连接
		bool connected;

		//是否已经startRevive
		bool TryReciving;

		/* 读缓冲的开始位置，一般为0
		 * 当开始了tryRecive之后才会变动
		 */
		size_t readBufbeg;
		// 缓冲结束位置
		size_t readBufend;
		//写缓冲中是否有数据
		bool writeBufHaveData;
		//读缓冲最大容量
		size_t readBufMaxLenth;
		//读缓冲
		char* readBuf;
		//写缓冲
		std::queue<Buffer> writeBuf;
		//锁
		::pthread_mutex_t mutex;
	};

}

#endif /* end of include guard: CONNECTER_H_TCUVAPLY */
