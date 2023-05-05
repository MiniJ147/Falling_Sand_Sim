#pragma once
#include "utils.h"

#define RETURN_MODE_POS 0
#define RETURN_MODE_TYPE 1 

struct Block
{
	U32 pos_size;
	U32 type_size;

	Vec2f* pos;
	U32* type;
};

void block_init(Block* block, U32 matrix_width,
			    U32 matrix_height,
			    U32 size_x, U32 size_y);

void block_create(Block block, U32 id, Vec2f pos, U32 type);

void block_render(Vec2f pos);
void block_tick(Vec2f* pos, U32 id, Block* matrix, 
				U32 matrix_width, U32 matrix_height);

void block_swap(Block block, U32 id_1, U32 id_2);
void* block_get_data(Block block, U32 id, U32 mode);