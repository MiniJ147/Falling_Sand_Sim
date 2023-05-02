#pragma once
#include "block.h"

#define WORLD_NULL_POS -1

struct World
{
    U32 width;
    U32 height;

    Block* matrix;
};

void world_init(World* world, U32 width, U32 height);
void world_release(World* world);

void world_create_block(Block* matrix, U32 matrix_width,
                        U32 x, U32 y, U32 id);

Block* world_get_block(Block* matrix, U32 matrix_width, 
                        U32 x, U32 y);