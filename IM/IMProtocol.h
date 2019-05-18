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


	//响应
	RESPONSE_LOGIN,



	INVALID
};


class IMPdu {
public:
	typedef uint64_t UserId;
	typedef uint32_t BodyLength;
	static const BodyLength BODY_MAX_LENGTH = BUFSIZ;
	static const size_t MIN_PDU_LENGTH = 
		sizeof(HEADER_BEGIN) + sizeof(size_t) + sizeof(IMPduCMD);

public:
	IMPdu () : headerLength(0), command(IMPduCMD::INVALID) { }
	virtual ~IMPdu() { }

	//get/set method /*{{{*/
	size_t getHeaderLenth() { return headerLength; }
	
	void setPduLength(size_t len) { headerLength = len; }

	UserId getUserId () { return userId; }

	void setUserId (UserId id) { userId = id; }

	IM::IMPduCMD getCommand () { return command; }

	void setCommand (IMPduCMD cmd) { command = cmd; }

/*}}}*/

	//序列化协议头信息， buf必须是可用的并且足够长的缓冲区
	virtual size_t serialization (char* buf) = 0; 

	//协议头最小长度
	static uint32_t getPduMinLength () {
		return MIN_PDU_LENGTH;
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

	void setPassword(const char* pwd);
	const char* getPassword();

private:
	char password[BUFSIZ];

};

class Logout : public IMPdu
{
public:
	Logout ();
	Logout (const char * buf, size_t len);
	virtual ~Logout () { }

	size_t serialization (char* buf) override;

};



class SendMsgPdu : public IMPdu
{
public:
	static const size_t MSG_MAX_LENGTH = BUFSIZ;
	SendMsgPdu ();
	SendMsgPdu (const char* buf, size_t len);
	virtual ~SendMsgPdu () { }

	size_t serialization (char* buf) override;
	const char* getBodyMsg (char* buf);

	void setBodyMsg(const char* msg,  size_t len);
	void setBodyMsg(const std::string msg, size_t len);

	void setObjID(UserId id) { objID = id; }
	UserId getObjID() { return objID; }

private:
	UserId objID;
	BodyLength bodyLength;
	char m_msg[MSG_MAX_LENGTH];

};

class ResponseLoginPdu : public IMPdu
{
public:
	enum STAT {
		SUCCEED,
		FAILD
		};

	ResponseLoginPdu () : m_stat(SUCCEED){
		command = RESPONSE_LOGIN;
   	}
	ResponseLoginPdu (STAT stat, const std::string msg) : m_stat(stat), m_msg(msg){
		command = RESPONSE_LOGIN;
   	}
	ResponseLoginPdu (const char* buf, size_t len); 
	virtual ~ResponseLoginPdu ();
	
	size_t serialization (char* buf) override;


protected:
	STAT m_stat;
	std::string m_msg;
};




/* 读取一个协议
 * 调用此函数之前必须保证connecter是一个已经开始了事务的连接
 * 即 已经调用了start_tryRecive方法
 */
std::shared_ptr<IMPdu> makeIMPdu(std::shared_ptr<Connecter> connecter_ptr);
std::shared_ptr<IMPdu> makeIMPdu(const char* buf);

size_t IMPduToSerivlization(char* buf, std::shared_ptr<IMPdu> pdu);

}
#endif /* end of include guard: IMPROTOCOL_H_RYFKP0LD */
