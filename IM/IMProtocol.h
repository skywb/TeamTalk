#ifndef IMPROTOCOL_H_RYFKP0LD
#define IMPROTOCOL_H_RYFKP0LD

#include <cstdio>
#include <iostream>
#include <memory>
#include <cstring>
#include <memory>

#include "reactor/Connecter.h"

namespace IM {

extern const uint16_t HEADER_BEGIN;

enum IMPduCMD {
	LOGIN, LOGOUT, 

	SENDMSG, 

	INVALID
};


class IMPdu {
public:
	typedef uint64_t UserId;
	typedef uint32_t BodyLength;
	static const BodyLength BODY_MAX_LENGTH = BUFSIZ;
	static const size_t MIN_HEADER_LENGTH = 
		sizeof(HEADER_BEGIN) + sizeof(size_t) + sizeof(IMPduCMD);

public:
	IMPdu () : headerLength(0), command(IMPduCMD::INVALID) { }
	virtual ~IMPdu() { }

	//get/set method /*{{{*/
	size_t getHeaderLenth() { return headerLength; }
	
	void setHeaderLength(size_t len) { headerLength = len; }

	UserId getUserId () { return userId; }

	void setUserId (UserId id) { userId = id; }

	IM::IMPduCMD getCommand () { return command; }

	void setCommand (IMPduCMD cmd) { command = cmd; }

	void setBodyMsg(const char* msg);
	void setBodyMsg(const std::string msg);


/*}}}*/

	//序列化协议头信息， buf必须是可用的并且足够长的缓冲区
	virtual size_t serialization (char* buf) = 0; 
	//写入协议体信息
	virtual const char* getBodyMsg (char* buf) {
		return nullptr;
	}

	//协议头最小长度
	static uint32_t getHeaderMinLength () {
		return MIN_HEADER_LENGTH;
	}

	//协议体最大长度
	static size_t getBodyMaxLength () {
		return BODY_MAX_LENGTH;
	}


protected:
	//用户ID
	size_t headerLength;
	//操作
	IMPduCMD command;

	UserId userId;
};


class LoginPdu : public IMPdu
{
public:
	LoginPdu ();
	LoginPdu (const char* buf, size_t headerLen);
	virtual ~LoginPdu () { }

	size_t serialization (char* buf) override;
	const char* getBodyMsg (char* buf) override;

	void setPassword(const char* pwd);
	const char* getPassword();

private:
	char password[BUFSIZ];

};

//class Logout : public IMPdu
//{
//public:
//	Logout ();
//	virtual ~Logout ();
//
//	size_t serialization (char* buf) override;
//
//private:
//	const char* getBodyMsg (char* buf) override;
//};
//
//
//
//class SendMsgPdu : public IMPdu
//{
//public:
//	SendMsgPdu ();
//	virtual ~SendMsgPdu ();
//
//	size_t serialization (char* buf) override;
//	const char* getBodyMsg (char* buf) override;
//
//	void setObjID(UserId id) { objID = id; }
//	UserId getObjID() { return objID; }
//
//private:
//	UserId objID;
//
//};
//


/* 读取一个协议
 * 调用此函数之前必须保证connecter是一个已经开始了事务的连接
 * 即 已经调用了start_tryRecive方法
 */
std::shared_ptr<IMPdu> makeIMPdu(std::shared_ptr<Connecter> connecter_ptr);
std::shared_ptr<IMPdu> makeIMPdu(const char* buf);

size_t IMPduToSerivlization(char* buf, std::shared_ptr<IMPdu> pdu);

}
#endif /* end of include guard: IMPROTOCOL_H_RYFKP0LD */
