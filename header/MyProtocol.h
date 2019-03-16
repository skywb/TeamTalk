#ifndef MYPROTOCOL_H_Y3UXGD6R
#define MYPROTOCOL_H_Y3UXGD6R

#include "User.h"
#include <sys/socket.h>
#include <cstring>

class MyProtocol
{
public:


	enum CMD {
		INVALID = 0,
		LOGIN = 1,
		LOGOUT = 2,
		SENDMSG = 3,
		ADDFRIEND = 4,
		HEAPPACKAGE = 5
	};

	MyProtocol () : _cmd(INVALID), _id(0), _objId(0) {
		memset(buf, 0, 1024);
	}

	MyProtocol (const char *p);
	virtual ~MyProtocol ();

	void setAccount(User::Account account) { _id = account; }
	void setObjAccount(User::Account account) { _objId = account; }
	void setMsgLength(unsigned int length) { _length = length; }
	void setMsg(const char * msg); 
	CMD getCmd() { return _cmd; }
	User::Account getAccount () { return _id; }
	User::Account getObjAccount () { return _objId; }
	char* getMsg();

	ssize_t send(int socket) {
		return write(socket, buf, strlen(buf));
	}

private:
	static size_t _headLength;
	static size_t _bodyLength;

	CMD _cmd;
	User::Account _id;
	User::Account _objId;
	unsigned int _length;
	char buf[1024];

	bool charToInt(unsigned int &num, const char* s, size_t len);

};

//第0位 CMD-'0', 1-10 自己ID， 11-20 目标ID, 最后3位 length
size_t MyProtocol::_headLength = 1 + 10 + 10 + 3;
// 999 + headlength  + 结束符 == 1024
size_t MyProtocol::_bodyLength = 999;





#endif /* end of include guard: MYPROTOCOL_H_Y3UXGD6R */