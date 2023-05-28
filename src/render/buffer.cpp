#include "buffer.h"

void buffer_init(Buffer* buf, U32 type, U32 count, size_t size, void* data, U32 usage)
{
	buf->count = count;
	buf->size = size;
	buf->type = type;

	glGenBuffers(count, &buf->buffer);
	buffer_bind(type, buf->buffer);
	glBufferData(type, size, data, usage);
}

void buffer_bind(U32 type, U32 buffer)
{
	glBindBuffer(type, buffer);
}
