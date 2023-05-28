#include "world.h"

void world_init(World* world, U32 width, U32 height)
{
    world->width = width;
    world->height = height;

    world->ids = (U32*)malloc(sizeof(U32) * (width * height));
    world->ids_size = width * height;

    //filling our matrix with proper data
    for (int i = 0; i < world->ids_size; i++)
    {
        *(world->ids + i) = i;
    }
}

//TODO add check to make sure we don't override already exisitng blocks when we add brushes
void world_create_block(Block* block, U32* ids, U32 matrix_width, float x, float y, U32 type)
{
    U32 id = world_get_id_val(ids, matrix_width, x, y);
    block_create(block, id, { x,y }, type);
}

void world_swap(Block block, U32* ids, U32 matrix_width, U32 x1, U32 y1, U32 x2, U32 y2)
{
    //swapping ids
    U32* id_1 = world_get_id_ptr(ids, matrix_width, x1, y1);
    U32* id_2 = world_get_id_ptr(ids, matrix_width, x2, y2);
    U32 temp = *id_1;

    //swaping in game world
    block_swap(block, *id_1, *id_2);

    //now swaping in matrix world
    *id_1 = *id_2;
    *id_2 = temp;
}

void world_release(World* world)
{
    free(world->ids);
}

void world_print_matrix(U32* ids, U32 matrix_width, U32 matrix_height)
{
    for (int y = 0; y < matrix_height; y++)
    {
        for (int x = 0; x < matrix_width; x++)
        {
            std::cout << world_get_id_val(ids, matrix_width, x, y) << " ";
        }
        std::cout << "\n";
    }
}

U32* world_get_id_ptr(U32* ids, U32 matrix_width, U32 x, U32 y)
{
    return((ids + (x + (matrix_width * y))));
}

U32 world_get_id_val(U32* ids, U32 matrix_width, U32 x, U32 y)
{
    return(*(ids + (x + (matrix_width * y))));
}