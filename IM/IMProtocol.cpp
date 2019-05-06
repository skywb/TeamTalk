#include <cstring>

#include "IMProtocol.h"
#include "util/UtilPdu.h"
#include "util/Log.h"


const uint16_t IM::HEADER_BEGIN = 0x1fff;

using namespace IM;

//从Connecter中读取, 解析协议， 返回一个IMPdu的智能指针
std::shared_ptr<IMPdu> IM::makeIMPdu(std::shared_ptr<Connecter> connecter_ptr) {

	char buf[BUFSIZ];
	size_t len = 0;
	size_t p = 0;
	IMPduCMD cmd = INVALID;
	connecter_ptr->startTryRecive(IM::IMPdu::getPduMinLength());
	try {
		//最小协议头包括开头信息，协议头长度， 以及cmd
		size_t re = connecter_ptr->tryRecive(buf, IMPdu::getPduMinLength());

		//不足最小协议头或者不符合协议格式
		if(re == 0 || 
			0 != ::memcmp(buf, &HEADER_BEGIN, sizeof(HEADER_BEGIN))) 
		{
			connecter_ptr->rollback_tryRecive();
			return nullptr;
		}

		p += sizeof(HEADER_BEGIN);
		//获取协议头长度
		len = *(size_t*)(buf+p);
		p += sizeof(size_t);

		cmd = *(IMPduCMD*)(buf+p);
		p += sizeof(IMPduCMD);

		//读取剩余部分
		if(len - p > 0) {
			re = connecter_ptr->tryRecive(buf+p, len-p);
			if(re == 0 || re < 0) {
				connecter_ptr->rollback_tryRecive();
				return nullptr;
			}
		}
		
		//校验长度
		if(p+re != len) {
			connecter_ptr->rollback_tryRecive();
			return nullptr;
		}
	
	}catch(TryReciveException &e) {
		connecter_ptr->rollback_tryRecive();
		char msg[BUFSIZ];
		sprintf(msg, "file %s : line %d: %s", __FILE__, __LINE__, e.what());
		Log::log(Log::ERROR, msg);
		throw;
	}

	std::shared_ptr<IMPdu> pdu;

	switch (cmd) {
		case LOGIN:
			pdu = std::make_shared<LoginPdu> (buf+IMPdu::getPduMinLength(), len-p);
			break;
		case LOGOUT:
			pdu = std::make_shared<Logout> (buf+p, len-p);
			break;
		case SENDMSG:
			pdu = std::make_shared<SendMsgPdu> (buf+p, len-p);
			break;
		case INVALID:
		default:
			return nullptr;
			break;
	}

	if(IMPduCMD::INVALID == pdu->getCommand()) 
	{
		connecter_ptr->rollback_tryRecive();
		pdu = nullptr;
	} else {
		connecter_ptr->commit_tryRecive();
	}
	pdu->setPduLength(len);
	return pdu;
}


std::shared_ptr<IMPdu> makeIMPdu(const char* buf) {

	size_t p = 0;
	size_t len = 0;
	IMPduCMD cmd = INVALID;
	//不足最小协议头或者不符合协议格式
	if(0 != ::memcmp(buf, &HEADER_BEGIN, sizeof(HEADER_BEGIN))) 
	{
		return nullptr;
	}

	p += sizeof(size_t);
	//获取协议头长度
	len = *(size_t*)(buf+p);
	p += sizeof(size_t);

	cmd = *(IMPduCMD*)(buf+p);
	p += sizeof(IMPduCMD);

	std::shared_ptr<IMPdu> pdu;

	switch (cmd) {
		case LOGIN:
			pdu = std::make_shared<LoginPdu> (buf+p, len-p);
			break;
		case LOGOUT:
			pdu = std::make_shared<Logout> (buf+p, len-p);
			break;
		case SENDMSG:
			pdu = std::make_shared<SendMsgPdu> (buf+p, len-p);
			break;
		case INVALID:
		default:
			return nullptr;
			break;
	}

	if(IMPduCMD::INVALID == pdu->getCommand()) 
	{
		pdu = nullptr;
	}
	pdu->setPduLength(len);
	return pdu;
}


size_t IM::IMPduToSerivlization(char* buf, std::shared_ptr<IMPdu> pdu) {

	size_t cur = 0;

	::memcpy(buf, &HEADER_BEGIN, sizeof(HEADER_BEGIN));
	cur += sizeof(HEADER_BEGIN);
	
	cur += sizeof(size_t);

	IMPduCMD cmd = pdu->getCommand();
	::memcpy(buf+cur, &cmd, sizeof(IMPduCMD));
	cur += sizeof(IMPduCMD);

	cur += pdu->serialization(buf+cur);

	::memcpy(buf+sizeof(HEADER_BEGIN), &cur, sizeof(size_t));
	pdu->setPduLength(cur);
	return  cur;
}

LoginPdu::LoginPdu() {
	setCommand(LOGIN);
}

LoginPdu::LoginPdu(const char* buf, size_t headerLen) {
	setCommand(LOGIN);
	size_t p = 0;
	::memcpy(&userId, buf, sizeof(UserId));
	p += sizeof(UserId);
	::memcpy(password, buf+p, headerLen-p);
}



size_t LoginPdu::serialization(char* buf) {
	size_t p = 0;
	::memcpy(buf, &userId, sizeof(UserId));
	p += sizeof(UserId);
	size_t len  = strlen(password);
	::strncpy(buf+p, password, len);
	p += len;
	return p;
}


void LoginPdu::setPassword(const char* pwd) {
	::strncpy(password, pwd, BUFSIZ);
}

const char* LoginPdu::getPassword() {
	return password;
}


Logout::Logout() {
	setCommand(LOGOUT);
}


Logout::Logout(const char* buf, size_t len) {
	setCommand(LOGOUT);
	userId = *(UserId*)(buf);
}


size_t Logout::serialization(char* buf) {
	size_t p = 0;
	::memcpy(buf, &userId, sizeof(UserId));
	p += sizeof(UserId);
	return p;
}

SendMsgPdu::SendMsgPdu() {
	setCommand(SENDMSG);
}


SendMsgPdu::SendMsgPdu (const char* buf, size_t len) {
	setCommand(SENDMSG);	
	size_t p = 0;
	::memcpy(&userId, buf, sizeof(UserId));
	userId = *(UserId*) buf;
	p += sizeof(UserId);
	objID = *(UserId*) (buf+p);
	p += sizeof(UserId);
	
	bodyLength = *(BodyLength*)(buf+p);
	p += sizeof(BodyLength);
	if(p + bodyLength != len || bodyLength > MSG_MAX_LENGTH) {
		setCommand(INVALID);
	}
	
	if(nullptr == ::strncpy(m_msg, buf+p, bodyLength)) {
		std::cout << "strncpy error" << std::endl;
	}
}


size_t SendMsgPdu::serialization (char* buf) {
	size_t p = 0;	
	::memcpy(buf+p, &userId, sizeof(UserId));
	p += sizeof(UserId);
	::memcpy(buf+p, &objID, sizeof(UserId));
	p += sizeof(UserId);

	::memcpy(buf+p, &bodyLength, sizeof(BodyLength));
	p += sizeof(BodyLength);

	::memcpy(buf+p, m_msg, bodyLength);

	return p+bodyLength;

}
const char* SendMsgPdu::getBodyMsg (char* buf) {
	::strncpy(buf, m_msg, bodyLength);
	return buf;
}


void SendMsgPdu::setBodyMsg(const char* msg, size_t len) {
	::strncpy(m_msg, msg, len);
	bodyLength = std::min(::strlen(m_msg), len);
}
void SendMsgPdu::setBodyMsg(const std::string msg, size_t len) {
	::strncpy(m_msg, msg.c_str(), len);
	bodyLength = std::min(::strlen(m_msg), len);
}






