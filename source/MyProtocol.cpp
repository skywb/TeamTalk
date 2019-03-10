#include <iostream>

#include "MyProtocol.h"



MyProtocol::MyProtocol(const char *p) {
	_cmd = (CMD)(p[0] - '0');

	if(!charToInt(_id, &p[1], 10)
			|| charToInt(_objId, &p[11], 10) 
			|| charToInt(_length, &p[21], 3)) {

		_cmd = INVALID;
		//log("协议格式错误");
		std::cout << "协议格式错误" << std::endl;

	}
}

void MyProtocol::setMsg(const char * msg) {
	if(strlen(msg) > _bodyLength) {
		//log("msg 超过最大限制");
	}
	size_t begin = _headLength;
	strncpy(buf+begin, msg, _bodyLength);
}

char* MyProtocol::getMsg() { 
	return &buf[_headLength];
}

bool MyProtocol::charToInt(unsigned int &num, const char* s, size_t len) {
	num = 0;
	for(size_t i=0; i<len; ++i)
		if(s[i] > '9' || s[i] < '0') return false;
		else {
			num *= 10;
			num += s[i] - '0';
		}
	return true;
}
