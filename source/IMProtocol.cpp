#include <cstring>

#include "IMProtocol.h"
#include "UtilPdu.h"
#include "Log.h"



using namespace IM;

//const uint32_t IMPdu::BUF_MAX_SIZE = 2048;
//
//IMPdu::IMPdu (IM::CMD command) {
//	m_header.command = static_cast<uint16_t>(command);
//	m_header.body_length = 0;
//	head_len = sizeof(m_header);
//}
//
//char* IMPdu::getBuffer() {
//	return m_buf;
//}
//
//uint32_t IMPdu::getLength() {
//	return m_header.body_length + m_header.header_length;
//}
//
//char* IMPdu::getBodyData() {
//	return m_buf+m_header.header_length;
//}
//uint32_t IMPdu::getBodyLength() {
//	return m_header.body_length;
//}
//IM::CMD IMPdu::getCommand() {
//	return IM::CMD(m_header.command);
//
//}
//
//void IMPdu::writeBody(const char* buf, uint32_t len) {
//	if(len + m_header.header_length > BUF_MAX_SIZE) return;
//	strncpy(m_buf, buf, len);
//	m_header.body_length = len;
//}
//void IMPdu::setCommand(IM::CMD cmd) {
//	m_header.command = cmd;
//}
//
//void IMPdu::writeHeader() {
//	::ByteStream::writeUint16(m_buf, m_header.command);
//	::ByteStream::writeUint32(m_buf+16, m_header.body_length);
//}
//
////static bool isProtocolAvailable(char* buf, uint32_t len, uint32_t& pdu_len);
//shared_ptr<IMPdu> IMPdu::readPdu(char* buf, uint32_t len) {
//	if(len < IMPduHeader::header_length) return nullptr;
//
//	uint16_t cmd = ::ByteStream::readUint16(buf);
//	auto res = make_shared<IMPdu>(IM::CMD(cmd));
//	
//}
//void write(char* buf, uint32_t len) { m_buf.write((void*)buf, len); }
//int readPduHeader(char* buf, uint32_t len);



IMPduHeader::IMPduHeader(const char* buf, size_t len) {
	/* * 读取根据buf内容，读取协议头信息
	 * <26-04-19, yourname> */
	headerLength = 0;
	userId = 0;
	objUserId = 0;
	bodyLength = 0;
	command = 0;
	command = *(CMD*)buf;
	headerLength += sizeof(CMD);
	switch (command) {
		case LOGIN:
			userId = *(UserId*)(buf+headerLength);
			headerLength += sizeof(UserId);
			bodyLength = *(BodyLength*)(buf+headerLength);
			headerLength += sizeof(bodyLength);
			break;
		case LOGOUT:
			userId = *(UserId*)(buf+headerLength);
			headerLength += sizeof(UserId);
			break;
		case SENDMSG:
			userId = *(UserId*)(buf+headerLength);
			headerLength += sizeof(UserId);
			objUserId = *(UserId*)(buf+headerLength);
			headerLength += sizeof(UserId);
			bodyLength = *(BodyLength*)(buf+headerLength);
			headerLength += sizeof(bodyLength);
			break;
		default:
			command = INVALID;
			break;
	}
	if(headerLength != len) 
		command = INVALID;
}



IMPduHeader* IMPduHeader::makeHeader(std::shared_ptr<Connecter> connecter_ptr) {
	char buf[getHeaderMaxLenth()];
	size_t len = 0;
	try {
		size_t re = connecter_ptr->tryRecive(buf, sizeof(HEADER_BEGIN));
		if(re == 0 || 
				sizeof(HEADER_BEGIN) != 
				::memcmp(buf, &HEADER_BEGIN, sizeof(HEADER_BEGIN))) 
		{

			return nullptr;
		}
		if(0 == connecter_ptr->tryRecive(buf, sizeof(size_t))) {
			return nullptr;
		}
		len = *(size_t*)buf;
		if(0 == connecter_ptr->tryRecive(buf, len)) {
			return nullptr;
		}
	
	}catch(TryReciveException &e) {
		char msg[BUFSIZ];
		sprintf(msg, "file %s : line %d: %s", __FILE__, __LINE__, e.what());
		Log::log(Log::ERROR, msg);
		throw;
	}
	IMPduHeader* header = new IMPduHeader(buf, len);
	if(IMPduHeader::INVALID == header->getCommand()) 
	{
		delete header;
		header = nullptr;
	}
	return header;
}



const char* IMPduHeader::getHeader (char* buf) {
	char* p = buf;
	size_t cur = 0;
	
	cur += sizeof(CMD);
	switch (command) {
		case LOGIN:
			userId = *(UserId*)(buf+cur);
			cur += sizeof(UserId);
			bodyLength = *(BodyLength*)(buf+cur);
			cur += sizeof(bodyLength);
			break;
		case LOGOUT:
			userId = *(UserId*)(buf+cur);
			cur += sizeof(UserId);
			break;
		case SENDMSG:
			userId = *(UserId*)(buf+cur);
			cur += sizeof(UserId);
			objUserId = *(UserId*)(buf+cur);
			cur += sizeof(UserId);
			bodyLength = *(BodyLength*)(buf+cur);
			cur += sizeof(bodyLength);
			break;
		default:
			command = INVALID;
			break;
	}
	if(cur != len) 
		command = INVALID;
}
















