#ifndef IMPROTOCOL_H_RYFKP0LD
#define IMPROTOCOL_H_RYFKP0LD

#include <cstdio>
#include <ostype.h>
#include <memory>

#include "cmd.h"
#include "UtilPdu.h"
namespace IM {

class IMPduHeader {

public:
	uint32_t body_length;
	static const uint32_t header_length = 32+16;
	uint16_t command;
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
	IMPduHeader m_header;
	char* m_buf;
	uint32_t head_len;
	static const uint32_t BUF_MAX_SIZE;
};

}
#endif /* end of include guard: IMPROTOCOL_H_RYFKP0LD */
