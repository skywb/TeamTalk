#ifndef IMPROTOCOL_H_RYFKP0LD
#define IMPROTOCOL_H_RYFKP0LD

#include <cstdio>
#include <ostype.h>
#include <memory.h>
#include <string.h>
#include <memory>

#include "cmd.h"
#include "UtilPdu.h"
namespace IM {

class IMPduHeader {
public:
	typedef uint64_t UserId;
	//typedef std::string Password;
	typedef uint32_t BodyLength;
	typedef uint16_t CMD;

	IMPduHeader () :  objUserId(0), bodyLength(0), command(0) {}

	static IMPduHeader* makeHeader() {

		/* TODO: 
		 * 读取一个协议头
		 * <25-04-19, sky> */

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

	const char* getHeader (char* buf) {
		char* p = buf;
		::memcpy(p, &HEADER_BEGIN, sizeof(HEADER_BEGIN));
		p += sizeof(HEADER_BEGIN);
		::memcpy(p, &userId, sizeof(UserId));
		p += sizeof(UserId);
		::memcpy(p, &objUserId, sizeof(UserId));
		p += sizeof(UserId);
		::memcpy(p, &bodyLength, sizeof(BodyLength));
		p += sizeof(BodyLength);
		::memcpy(p, &command, sizeof(CMD));
		return buf;
	}

	static uint32_t getHeaderLenth () {
		return HEADER_LENGTH;
	}


	static size_t getBodyMaxLength () {
		return BODY_MAX_LENGTH;
	}


private:
	//用户ID
	UserId userId;
	//好友ID, 若非发送消息， 则为空
	UserId objUserId;
	//消息长度
	BodyLength bodyLength;
	//操作
	CMD command;

	static const uint8_t HEADER_BEGIN = 0xff;
	static const uint32_t HEADER_LENGTH = sizeof(HEADER_BEGIN) + sizeof(UserId) + sizeof(UserId) + sizeof(BodyLength) + sizeof(CMD);
	static const size_t BODY_MAX_LENGTH = 2048;

public:
	//未登录命令
	static const uint16_t LOGIN = 0x1ff;

	//在线命令
	static const uint16_t SENDMSG = 0xf1f;

	//其他命令
	static const uint16_t INVALID = 0xff1;
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
