#include <cstring>

#include "IMProtocol.h"
#include "util/UtilPdu.h"
#include "util/Log.h"


const uint16_t IM::HEADER_BEGIN = 0x1fff;

using namespace IM;

//IMPdu::IMPdu(const char* buf, size_t len) {
//	/* * 读取根据buf内容，读取协议头信息
//	 * <26-04-19, yourname> */
//	headerLength = 0;
//	userId = 0;
//	objUserId = 0;
//	bodyLength = 0;
//	command = *(IMPduCMD*)buf;
//	headerLength += sizeof(IMPduCMD);
//
//	
//
//	switch (command) {
//		case LOGIN:
//			userId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			bodyLength = *(BodyLength*)(buf+headerLength);
//			headerLength += sizeof(bodyLength);
//			break;
//		case LOGOUT:
//			userId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			break;
//		case SENDMSG:
//			userId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			objUserId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			bodyLength = *(BodyLength*)(buf+headerLength);
//			headerLength += sizeof(bodyLength);
//			break;
//		default:
//			command = INVALID;
//			break;
//	}
//
//	if(headerLength != len) 
//	{
//		command = INVALID;
//	}
//
//}


//IMPdu::IMPdu(const char* buf) {
//	/* * 读取根据buf内容，读取协议信息
//	 * <26-04-19, sky> */
//
//	headerLength = 0;
//	userId = 0;
//	command = INVALID;
//
//
//	if( 0 != ::memcmp(buf, &HEADER_BEGIN, sizeof(HEADER_BEGIN))) {
//		Log::log(Log::INFO, "IMPdu failed");
//		command = INVALID;
//		return;
//	}
//
//	headerLength += sizeof(HEADER_BEGIN);
//	size_t len = *(size_t*)(buf+headerLength);
//	headerLength += sizeof(size_t);
//
//
//	command = *(IMPduCMD*)(buf + headerLength);
//	headerLength += sizeof(IMPduCMD);
//	switch (command) {
//		case LOGIN:
//			userId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			bodyLength = *(BodyLength*)(buf+headerLength);
//			headerLength += sizeof(bodyLength);
//			break;
//		case LOGOUT:
//			userId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			break;
//		case SENDMSG:
//			userId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			objUserId = *(UserId*)(buf+headerLength);
//			headerLength += sizeof(UserId);
//			bodyLength = *(BodyLength*)(buf+headerLength);
//			headerLength += sizeof(bodyLength);
//			break;
//		default:
//			command = INVALID;
//			break;
//	}
//
//	if(headerLength != len) 
//		command = INVALID;
//
//}


//从Connecter中读取, 解析协议， 返回一个IMPdu的智能指针
std::shared_ptr<IMPdu> IM::makeIMPdu(std::shared_ptr<Connecter> connecter_ptr) {

	char buf[BUFSIZ];
	size_t len = 0;
	size_t p = 0;
	IMPduCMD cmd = INVALID;
	connecter_ptr->startTryRecive(IM::IMPdu::getHeaderMinLength());
	try {
		//最小协议头包括开头信息，协议头长度， 以及cmd
		size_t re = connecter_ptr->tryRecive(buf, IMPdu::getHeaderMinLength());

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
		re = connecter_ptr->tryRecive(buf+p, len-p);
		if(re == 0 || re < 0) {
			connecter_ptr->rollback_tryRecive();
			return nullptr;
		}
		p += len-p;
		//不会发生
		if(p != len) {
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
			pdu = std::make_shared<LoginPdu> (buf+IMPdu::getHeaderMinLength(), len);
			break;
		//case LOGOUT:
		//	pdu = std::make_shared<Logout> (buf+p);
		//	break;
		//case SENDMSG:
		//	pdu = std::make_shared<SendMsgPdu> (buf+p);
		//	break;
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
			pdu = std::make_shared<LoginPdu> (buf+p, len);
			break;
		//case LOGOUT:
		//	pdu = std::make_shared<Logout> (buf+p);
		//	break;
		//case SENDMSG:
		//	pdu = std::make_shared<SendMsgPdu> (buf+p);
		//	break;
		case INVALID:
		default:
			return nullptr;
			break;
	}

	if(IMPduCMD::INVALID == pdu->getCommand()) 
	{
		pdu = nullptr;
	}
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
	std::cout << cur << std::endl;
	return  cur;
}

LoginPdu::LoginPdu() {
	setCommand(LOGIN);
}

LoginPdu::LoginPdu(const char* buf, size_t headerLen) {
	setCommand(LOGIN);
	headerLength = headerLen;
	size_t p = 0;
	::memcpy(&userId, buf, sizeof(UserId));
	p += sizeof(UserId);
	::memcpy(password, buf+p, headerLength-p);
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

const char* LoginPdu::getBodyMsg (char* buf) {
	::strncpy(buf, password, BUFSIZ);
	return buf;
}

void LoginPdu::setPassword(const char* pwd) {
	::strncpy(password, pwd, BUFSIZ);
}

const char* LoginPdu::getPassword() {
	return password;
}


/*
const char* IMPdu::getHeader(char *buf) {
	size_t cur = 0;

	//::memcpy(buf, &HEADER_BEGIN, sizeof(HEADER_BEGIN));
	::memcpy((void*)buf, (void*)&HEADER_BEGIN, sizeof(HEADER_BEGIN));
	cur += sizeof(HEADER_BEGIN);
	
	//::memcpy(buf+cur, &headerLength, sizeof(headerLength));
	cur += sizeof(headerLength);

	::memcpy(buf+cur, &command, sizeof(IMPduCMD));
	cur += sizeof(IMPduCMD);
	switch (command) {
		case LOGIN:
			::memcpy(buf+cur, &userId, sizeof(UserId));
			cur += sizeof(UserId);
			::memcpy(buf+cur, &bodyLength, sizeof(BodyLength));
			cur += sizeof(bodyLength);
			break;
		case LOGOUT:
			::memcpy(buf+cur, &userId, sizeof(UserId));
			cur += sizeof(UserId);
			break;
		case SENDMSG:
			::memcpy(buf+cur, &userId, sizeof(UserId));
			cur += sizeof(UserId);
			::memcpy(buf+cur, &objUserId, sizeof(UserId));
			cur += sizeof(UserId);
			::memcpy(buf+cur, &bodyLength, sizeof(BodyLength));
			cur += sizeof(bodyLength);
			break;
		default:
			command = INVALID;
			break;
	}
	headerLength = cur;

	::memcpy(buf+sizeof(HEADER_BEGIN), &headerLength, sizeof(headerLength));
	return buf;
}
*/

