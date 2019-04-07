#ifndef UTILPDU_H_
#define UTILPDU_H_

#include "ostype.h"
#include <set>
#include <map>
#include <list>
#include <string>
#include <stdint.h>


using namespace std;


// exception code
#define ERROR_CODE_PARSE_FAILED 		1
#define ERROR_CODE_WRONG_SERVICE_ID		2
#define ERROR_CODE_WRONG_COMMAND_ID		3
#define ERROR_CODE_ALLOC_FAILED			4

/*
class CPduException {
public:
	CPduException(uint32_t service_id, uint32_t command_id, uint32_t error_code, const char* error_msg)
	{
		m_service_id = service_id;
		m_command_id = command_id;
		m_error_code = error_code;
		m_error_msg = error_msg;
	}

	CPduException(uint32_t error_code, const char* error_msg)
	{
		m_service_id = 0;
		m_command_id = 0;
		m_error_code = error_code;
		m_error_msg = error_msg;
	}

	virtual ~CPduException() {}

	uint32_t GetServiceId() { return m_service_id; }
	uint32_t GetCommandId() { return m_command_id; }
	uint32_t GetErrorCode() { return m_error_code; }
	char* GetErrorMsg() { return (char*)m_error_msg.c_str(); }
private:
	uint32_t	m_service_id;
	uint32_t	m_command_id;
	uint32_t	m_error_code;
	string		m_error_msg;
};
*/

class CSimpleBuffer
{
public:
	CSimpleBuffer();
	~CSimpleBuffer();
	char*  getBuffer() { return m_buffer; }
	uint32_t getAllocSize() { return m_alloc_size; }
	uint32_t getWriteOffset() { return m_write_offset; }
	void extend(uint32_t len);

	uint32_t write(void* buf, uint32_t len);
	uint32_t read(void* buf, uint32_t len);
protected:
	void incWriteOffset(uint32_t len) { m_write_offset += len; }

private:
	char*	m_buffer;
	uint32_t	m_alloc_size;
	uint32_t	m_write_offset;
};


class ByteStream
{
public:

	static int16_t readInt16(char* buf);
	static uint16_t readUint16(char* buf);
	static int32_t readInt32(char* buf);
	static uint32_t readUint32(char* buf);
	static void writeInt16(char* buf, int16_t data);
	static void writeUint16(char* buf, uint16_t data);
	static void writeInt32(char* buf, int32_t data);
	static void writeUint32(char* buf, uint32_t data);

};


#endif /* UTILPDU_H_ */
