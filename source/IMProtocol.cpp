#include "IMProtocol.h"
#include "UtilPdu.h"
#include <cstring>

namespace IM {

const uint32_t IMPdu::BUF_MAX_SIZE = 2048;

IMPdu::IMPdu (IM::CMD command) {
	m_header.command = static_cast<uint16_t>(command);
	m_header.body_length = 0;
	head_len = sizeof(m_header);
}

char* IMPdu::getBuffer() {
	return m_buf;
}

uint32_t IMPdu::getLength() {
	return m_header.body_length + m_header.header_length;
}

char* IMPdu::getBodyData() {
	return m_buf+m_header.header_length;
}
uint32_t IMPdu::getBodyLength() {
	return m_header.body_length;
}
IM::CMD IMPdu::getCommand() {
	return IM::CMD(m_header.command);

}

void IMPdu::writeBody(const char* buf, uint32_t len) {
	if(len + m_header.header_length > BUF_MAX_SIZE) return;
	strncpy(m_buf, buf, len);
	m_header.body_length = len;
}
void IMPdu::setCommand(IM::CMD cmd) {
	m_header.command = cmd;
}

void IMPdu::writeHeader() {
	::ByteStream::writeUint16(m_buf, m_header.command);
	::ByteStream::writeUint32(m_buf+16, m_header.body_length);
}

//static bool isProtocolAvailable(char* buf, uint32_t len, uint32_t& pdu_len);
shared_ptr<IMPdu> IMPdu::readPdu(char* buf, uint32_t len) {
	if(len < IMPduHeader::header_length) return nullptr;

	uint16_t cmd = ::ByteStream::readUint16(buf);
	auto res = make_shared<IMPdu>(IM::CMD(cmd));
	
}
void write(char* buf, uint32_t len) { m_buf.write((void*)buf, len); }
int readPduHeader(char* buf, uint32_t len);
}
