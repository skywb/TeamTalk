#ifndef IMPROTOCOL_H_RYFKP0LD
#define IMPROTOCOL_H_RYFKP0LD

#include <cstdio>
//#include <ostype.h>
#include <memory.h>
#include <string.h>
#include <memory>

#include "cmd.h"
#include "util/UtilPdu.h"
#include "reactor/Connecter.h"

namespace IM {

class IMPduHeader {
public:
	typedef uint64_t UserId;
	//typedef std::string Password;
	typedef uint32_t BodyLength;
	typedef uint16_t CMD;

	IMPduHeader () : headerLength(0), objUserId(0), bodyLength(0), command(INVALID) {}
	IMPduHeader (const char* buf, size_t len);

	/* 读取一个协议头
	 * 调用此函数之前必须保证connecter是一个已经开始了事务的连接
	 * 即 已经调用了start_tryRecive方法
	 */
	static IMPduHeader* makeHeader(std::shared_ptr<Connecter> connecter_ptr);

	size_t getHeaderLenth() {
		return headerLength;
	}
	
	void setHeaderLength(size_t len) {
		headerLength = len;
	}

	UserId getUserId () {
		return userId;
	}

	void setUserId (UserId id) {
		userId = id;
	}

	UserId getObjUserId () {
		return objUserId;
	}

	void setObjUserId (UserId id) {
		objUserId = id;
	}

	BodyLength getBodyLength () {
		return bodyLength;
	}

	void setBodyLength (BodyLength len) {
		bodyLength = len;
	}

	CMD getCommand () {
		return command;
	}

	void setCommand (CMD cmd) {
		command = cmd;
	}

	const char* getHeader (char* buf); 

	static uint32_t getHeaderMaxLenth () {
		return HEADER_MAX_LENGTH;
	}


	static size_t getBodyMaxLength () {
		return BODY_MAX_LENGTH;
	}


private:
	//用户ID
	size_t headerLength;
	UserId userId;
	//好友ID, 若非发送消息， 则为空
	UserId objUserId;
	//消息长度
	BodyLength bodyLength;
	//操作
	CMD command;

	static const uint8_t HEADER_BEGIN = 0xff;
	static const uint32_t HEADER_MAX_LENGTH = sizeof(HEADER_BEGIN) + sizeof(UserId) + sizeof(UserId) + sizeof(BodyLength) + sizeof(CMD);
	static const size_t BODY_MAX_LENGTH = 2048;

public:
	//未登录命令
	static const CMD LOGIN = 0x1ff;
	static const CMD LOGOUT = 0x2ff;

	//在线命令
	static const CMD SENDMSG = 0xf1f;

	//其他命令
	static const CMD INVALID = 0xff1;
};


class IMPdu
{
public:
	IMPdu (IM::CMD command);
	virtual ~IMPdu () {}


	char* getBuffer();
	uint32_t getLength();
	char* getBodyData();
	uint32_t getBodyLength();
	IM::CMD getCommand();

	void writeBody(const char* buf, uint32_t len);
	void setCommand(IM::CMD cmd);
	void writeHeader();

	//static bool isProtocolAvailable(char* buf, uint32_t len, uint32_t& pdu_len);
	static shared_ptr<IMPdu> readPdu(char* buf, uint32_t len);
	void write(char* buf, uint32_t len);
	int readPduHeader(char* buf, uint32_t len);

private:
	static const uint32_t BUF_MAX_SIZE = 2048 + 100;

	IMPduHeader header;
	char buf[BUF_MAX_SIZE];
	uint32_t head_len;
};

}
#endif /* end of include guard: IMPROTOCOL_H_RYFKP0LD */
