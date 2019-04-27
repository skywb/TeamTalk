#include "UtilPdu.h"
#include <stdlib.h>
#include <string.h>

///////////// CSimpleBuffer ////////////////
CSimpleBuffer::CSimpleBuffer()
{
	m_buffer = NULL;
	m_alloc_size = 0;
	m_write_offset = 0;
}

CSimpleBuffer::~CSimpleBuffer()
{
	m_alloc_size = 0;
	m_write_offset = 0;
	if (m_buffer)
	{
		free(m_buffer);
		m_buffer = NULL;
	}
}

void CSimpleBuffer::extend(uint32_t len)
{
	m_alloc_size = m_write_offset + len;
	m_alloc_size += m_alloc_size >> 2;	// increase by 1/4 allocate size
	char* new_buf = (char*)realloc(m_buffer, m_alloc_size);
	m_buffer = new_buf;
}

uint32_t CSimpleBuffer::write(void* buf, uint32_t len)
{
	if (m_write_offset + len > m_alloc_size)
	{
		extend(len);
	}

	if (buf)
	{
		memcpy(m_buffer + m_write_offset, buf, len);
	}

	m_write_offset += len;

	return len;
}

uint32_t CSimpleBuffer::read(void* buf, uint32_t len)
{
	if (len > m_write_offset)
		len = m_write_offset;

	if (buf)
		memcpy(buf, m_buffer, len);

	m_write_offset -= len;
	memmove(m_buffer, m_buffer + len, m_write_offset);
	return len;
}


int16_t ByteStream::readInt16(char *buf)
{
	int16_t data = (buf[0] << 8) | buf[1];
	return data;
}

uint16_t ByteStream::readUint16(char* buf)
{
	uint16_t data = (buf[0] << 8) | buf[1];
	return data;
}

int32_t ByteStream::readInt32(char *buf)
{
	int32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	return data;
}

uint32_t ByteStream::readUint32(char *buf)
{
	uint32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	return data;
}

void ByteStream::writeInt16(char *buf, int16_t data)
{
	buf[0] = static_cast<char>(data >> 8);
	buf[1] = static_cast<char>(data & 0xFF);
}

void ByteStream::writeUint16(char *buf, uint16_t data)
{
	buf[0] = static_cast<char>(data >> 8);
	buf[1] = static_cast<char>(data & 0xFF);
}

void ByteStream::writeInt32(char *buf, int32_t data)
{
	buf[0] = static_cast<char>(data >> 24);
	buf[1] = static_cast<char>((data >> 16) & 0xFF);
	buf[2] = static_cast<char>((data >> 8) & 0xFF);
	buf[3] = static_cast<char>(data & 0xFF);
}

void ByteStream::writeUint32(char *buf, uint32_t data)
{
	buf[0] = static_cast<char>(data >> 24);
	buf[1] = static_cast<char>((data >> 16) & 0xFF);
	buf[2] = static_cast<char>((data >> 8) & 0xFF);
	buf[3] = static_cast<char>(data & 0xFF);
}
