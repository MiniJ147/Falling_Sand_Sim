#pragma once
#include "../utils.h"
#include <glad/glad.h>

struct Buffer
{
	U32 buffer, type, count;
	size_t size;
};

void buffer_init(Buffer* buf, U32 type, U32 count, size_t size, void* data, U32 usage);
void buffer_bind(U32 type, U32 buffer);