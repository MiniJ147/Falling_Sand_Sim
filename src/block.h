#pragma once
#include "utils.h"

struct Block
{
	Vec2f pos;
	U32 id;
};

void block_init(U32 size_x, U32 size_y);
void block_create(Block* b, Vec2f pos, U32 id);

void block_render(Vec2f pos, U32 id);
void block_tick(Vec2f* pos, U32 id, Block* matrix, 
				U32 matrix_width, U32 matrix_height);