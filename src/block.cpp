#include "block.h"
#include "render/buffer.h"
#include "render/shader.h"
#include "global.h"
#include "world.h"
#include <glad/glad.h>

glm::vec3 colors[] = { glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f)};

struct Size
{
	U32 x;
	U32 y;
}size;

struct Orgin_Adjust
{
	float x;
	float y;
}orgin_adjust;

static Buffer* vb = (Buffer*)malloc(sizeof(Buffer));
static Buffer* ib = (Buffer*)malloc(sizeof(Buffer));
static U32 shader;
static U32 vao;

static float vertices[] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	-0.5f,  0.5f,
	 0.5f,  0.5f
};

static U32 indices[] = {
	0,1,3,
	0,2,3
};

void block_init(Block* block, U32 matrix_width, U32 matrix_height, U32 size_x, U32 size_y)
{
	size.x = size_x;
	size.y = size_y;

	std::cout << size_x << " " << size_y << std::endl;

	orgin_adjust.x = (-1.f * global_get()->window_width / 2) + size.x / 2;
	orgin_adjust.y = (global_get()->window_height / 2) - size.y / 2;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	buffer_init(vb, GL_ARRAY_BUFFER, 1, sizeof(vertices), vertices, GL_STATIC_DRAW);
	buffer_bind(vb->type, vb->buffer);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	buffer_init(ib, GL_ELEMENT_ARRAY_BUFFER, 1, sizeof(indices), indices, GL_STATIC_DRAW);
	buffer_bind(ib->type, ib->buffer);

	char* pv = shader_file_parse("src/render/shaders/block_vert.glsl");
	char* pf = shader_file_parse("src/render/shaders/block_frag.glsl");

	shader = shader_create(pv, pf);

	//declaring these arrays with the size of the 
	const U32 MATRIX_SIZE = matrix_width * matrix_height;
	block->pos_size = MATRIX_SIZE;
	block->type_size = MATRIX_SIZE;
	block->weight_size = MATRIX_SIZE;

	block->pos = (Vec2f*)malloc(sizeof(Vec2f) * block->pos_size);
	block->type = (U32*)malloc(sizeof(U32) * block->type_size);
	block->weight = (U32*)malloc(sizeof(U32) * block->weight_size);

	//setting memory to the null identifier 
	memset(block->pos, WORLD_NULL, sizeof(Vec2f) * block->pos_size);
	memset(block->type, WORLD_NULL, sizeof(U32) * block->type_size);
	memset(block->weight, WORLD_NULL, sizeof(U32) * block->weight_size);
}

void block_swap(Block block, U32 id_1, U32 id_2)
{
	Vec2f* pos_1 = (Vec2f*)block_get_data_ptr(block, id_1, RETURN_MODE_POS);
	Vec2f* pos_2 = (Vec2f*)block_get_data_ptr(block, id_2, RETURN_MODE_POS);
	Vec2f temp = *pos_2;

	*pos_2 = *pos_1;
	*pos_1 = temp;

	/*U32* type_1 = (U32*)block_get_data_ptr(block, id_1, RETURN_MODE_TYPE);
	U32* type_2 = (U32*)block_get_data_ptr(block, id_2, RETURN_MODE_TYPE);
	U32 _temp = *type_2;

	*type_2 = *type_1;
	*type_1 = _temp;*/
}

void block_create(Block* block, U32 id, Vec2f pos, U32 type, U32 weight)
{
	switch (type)
	{
	//remove this id from any tick or render function because it is no longer its other data type
	case AIR:
		//remove this id from render ids
		if (block->render_ids.size() > 0);

		//remove this id from tickable ids
		if (block->tickable_ids.size() > 0);
	break;

	//add the id to the render and tick function 
	case SAND:
		block->render_ids.push_back(id);
		block->tickable_ids.push_back(id);

		//if this lags the program add the check to make sure when we push data it needs to be sorted
		bubble_sort(block->render_ids);
		bubble_sort(block->tickable_ids);

		break;
	}
	//grabbing the ptr and setting its data to our desired data
	*(Vec2f*)block_get_data_ptr(*block, id, RETURN_MODE_POS) = pos;
	*(U32*)block_get_data_ptr(*block, id, RETURN_MODE_TYPE) = type;
	*(U32*)block_get_data_ptr(*block, id, RETURN_MODE_WEIGHT) = weight;
}

void* block_get_data_ptr(Block block, U32 id, U32 mode)
{
	switch (mode)
	{
	case RETURN_MODE_POS:
		return (void*)(block.pos + id);
		break;

	case RETURN_MODE_TYPE:
		return (void*)(block.type + id);
		break;
	case RETURN_MODE_WEIGHT:
		return (void*)(block.weight + id);
		break;
	default:
		return nullptr;
	}
}

Cell block_get_data_cell(Block block, U32 id)
{
	return Cell{ *(block.pos + id),*(block.type + id),*(block.weight + id), id};
}

Cell block_get_data_cell(Block block, U32* ids, U32 matrix_width, U32 x, U32 y)
{
	U32 id = world_get_id_val(ids, matrix_width, x, y);
	return Cell{ *(block.pos + id),*(block.type + id),*(block.weight + id), id };
}

bool block_move(Block block, U32* ids, U32 matrix_width, Cell curr, Cell next)
{
	if (curr.weight > next.weight)
	{
		world_swap(block, ids, matrix_width, curr.pos.x, curr.pos.y, next.pos.x, next.pos.y);
		LOG("PREFROMED SWAP");
		return true;
	}
	return false;
}

void block_tick(Block* block, U32 curr_id, U32* ids, U32 matrix_width, U32 matrix_height)
{
	//TODO create basic ticking system for now we are just going to print the data of the block below us
	Cell curr_data = block_get_data_cell(*block, curr_id);
	U32 curr_type = curr_data.type;

	switch (curr_type)
	{
	case SAND:
		//checking below
		if (curr_data.pos.y + 1 >= matrix_height)
			return;

		//move down
		Cell next_data = block_get_data_cell(*block, ids, matrix_width, curr_data.pos.x, curr_data.pos.y + 1);
		if (block_move(*block, ids, matrix_width, curr_data, next_data))
			return;

		if (curr_data.pos.x + 1 >= matrix_width)
		{
			if (curr_data.pos.x - 1 < 0)
				return;
			
			//move left
			next_data = block_get_data_cell(*block, ids, matrix_width, curr_data.pos.x - 1, curr_data.pos.y + 1);
			block_move(*block, ids, matrix_width, curr_data, next_data);
			return;
		}

		//move right
		next_data = block_get_data_cell(*block, ids, matrix_width, curr_data.pos.x + 1, curr_data.pos.y + 1);
		if (block_move(*block, ids, matrix_width, curr_data, next_data))
			return;

		if (curr_data.pos.x - 1 < 0)
			return;

		//move left
		next_data = block_get_data_cell(*block, ids, matrix_width, curr_data.pos.x - 1, curr_data.pos.y + 1);
		block_move(*block, ids, matrix_width, curr_data, next_data);

		break;
	}
}

void block_render(Cell c)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 mvp(1.0f);

	glBindVertexArray(vao);
	buffer_bind(vb->type, vb->buffer);
	buffer_bind(ib->type, ib->buffer);

	glUseProgram(shader);

	Global_Data* g_d = global_get();

	view = glm::translate(view, glm::vec3(orgin_adjust.x + (c.pos.x * size.x), orgin_adjust.y - (c.pos.y * size.y), 0.f));

	model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));

	mvp = global_get()->projection * view * model;

	shader_uniform_set_mat4(shader, "u_mvp", mvp);
	shader_uniform_set_vec3(shader, "color", colors[c.type]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}