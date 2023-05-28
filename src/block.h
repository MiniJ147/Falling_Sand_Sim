#pragma once
#include "utils.h"
#include <vector>

#define RETURN_MODE_POS 0
#define RETURN_MODE_TYPE 1 

#define AIR 0
#define SAND 1

struct Block
{
	U32 pos_size;
	U32 type_size;

	Vec2f* pos;
	U32* type;

	std::vector<U32>render_ids;
	std::vector<U32>tickable_ids;
};

struct Cell
{
	Vec2f pos;
	U32 type;
};

void block_init(Block* block, U32 matrix_width,
	U32 matrix_height,
	U32 size_x, U32 size_y);

void block_create(Block* block, U32 id, Vec2f pos, U32 type);

void block_render(Cell c);
void block_tick(Block* block, U32 id, U32* matrix,
	U32 matrix_width);

void block_swap(Block block, U32 id_1, U32 id_2);
void* block_get_data_ptr(Block block, U32 id, U32 mode);
Cell block_get_data_cell(Block block, U32 id);