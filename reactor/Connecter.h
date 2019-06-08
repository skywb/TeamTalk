#ifndef CONNECTER_H_TCUVAPLY
#define CONNECTER_H_TCUVAPLY

#include <memory>
#include <mutex>
#include <memory>
#include <cstring>
#include <queue>
#include <vector>
#include <pthread.h>

#include "reactor/Addresser.h"
#include "util/sockUtil.h"
#include "IM/IMProtocol.pb.h"


namespace IM {

	/* 数据缓冲区， 可以暂存数据
	 */

	class Buffer {/*{{{*/
	public:
		Buffer () :  _begin(0), buf(nullptr), _end(0) {}
		Buffer (const char* str, size_t len) {
			_end = len;
			if(_end > MSGMAXSIZE) {
				//log(error);
				buf = nullptr;
			} else {
				buf = new char[MSGMAXSIZE];
				::memcpy(buf, str, _end);
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
	};/*}}}*/

	class TryReciveException : public std::exception {/*{{{*/
	public:
		TryReciveException (const char* msg) :msg(msg) {}
		virtual ~TryReciveException () {}

		const char* what() const throw() {
			return msg;
		}
	
	private:
		const char* msg;
	};/*}}}*/


	class Connecter {
	public:
		Connecter(int _sockfd) : 
			sockfd(_sockfd), readable(true), writeable(true),
		   	readBufbeg(0), readBufend(0), writeBufHaveData(false), readBufMaxLenth(BUFSIZ*2)
		{
			readBuf = (char*)::malloc(BUFSIZ*2);
		}

		virtual ~Connecter() {
			::free(readBuf);
			::close(sockfd);
		}


		//读取数据
		virtual int send(const char* msg, size_t len);
		virtual int recive(char* buf, size_t minLength = 0);

		virtual void readToBuffer();

		virtual void closeThisConnecter();
		//virtual void deleteThisConnecter();

		//可写回调函数， 若所有数据都写完则返回true， 反之返回false
		virtual bool onWriteable();

		virtual bool isConnected() {
			std::lock_guard<std::mutex> lock(m_mutex);
			bool stat = writeable | readable;
			return stat; 
		}
	
	protected:

		//正在连接的socket
		int sockfd;
		bool readable;
		bool writeable;

		//是否已经startRevive
		//bool TryReciving;

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
		//::pthread_mutex_t mutex;
		std::mutex m_mutex;
	};




	class IMConn : public Connecter
	{
	public:
		IMConn (int sockfd) : Connecter(sockfd) { }
		//IMConn (const char* IP, const uint16_t port);
		virtual ~IMConn () {}

		bool send(Proto::Response* response);
		Proto::Request* recive();
	};

	class ClientConn : public Connecter
	{
	public:
		ClientConn (int sockfd) : Connecter(sockfd) {
			sockUtil::setNoBlock(sockfd);
	   	}
		ClientConn (const char* IP, const uint16_t port);
		virtual ~ClientConn () {}


		void waitMsg();

		bool send(Proto::Request* request);
		Proto::Response* recive();
	};
}

#endif /* end of include guard: CONNECTER_H_TCUVAPLY */
