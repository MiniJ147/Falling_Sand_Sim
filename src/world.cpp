#include "world.h"

void world_init(World* world, U32 width, U32 height)
{
    world->width=width;
    world->height=height;
    
    world->matrix = (Block*)malloc(sizeof(Block)*(width*height));
    memset(world->matrix,-1,sizeof(Block)*(width*height));
}

void world_release(World* world)
{
    free(world->matrix);
}

void world_create_block(Block* matrix, U32 matrix_width, U32 x, U32 y, U32 id)
{
    block_create(world_get_block(matrix,matrix_width,x,y),{(float)x,(float)y},id);
}

Block* world_get_block(Block* matrix, U32 matrix_width, U32 x, U32 y)
{
    return (matrix+(x+(matrix_width*y)));
}