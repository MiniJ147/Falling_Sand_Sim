#pragma once
#include "block.h"

#define WORLD_NULL -1

struct World
{
    U32 width;
    U32 height;

    U32 ids_size;
    U32* ids;
};

void world_init(World* world, U32 width, U32 height);
void world_release(World* world);

//void world_create_block(Block* matrix, U32 matrix_width,
//                        U32 x, U32 y, U32 id);

//returns ptr
U32* world_get_id_ptr(U32* ids, U32 matrix_width,
    U32 x, U32 y);

U32 world_get_id_val(U32* ids, U32 matrix_width,
    U32 x, U32 y);

void world_create_block(Block* block, U32* ids, U32 matrix_width,
    float x, float y, U32 type);

void world_swap(Block block, U32* ids, U32 matrix_width,
    U32 x1, U32 y1, U32 x2, U32 y2);

void world_print_matrix(U32* ids, U32 matrix_width,
    U32 matrix_height);