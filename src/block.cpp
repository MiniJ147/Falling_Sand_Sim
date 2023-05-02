#include "block.h"
#include "buffer.h"
#include "shader.h"
#include "global.h"
#include <glad/glad.h>

struct Size
{
	U32 x;
	U32 y;
}size;

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

void block_init(U32 size_x, U32 size_y)
{
	size.x=size_x;
	size.y=size_y;

	std::cout<<size_x<<" "<<size_y<<std::endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	buffer_init(vb, GL_ARRAY_BUFFER, 1, sizeof(vertices), vertices, GL_STATIC_DRAW);
	buffer_bind(vb->type, vb->buffer);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	buffer_init(ib, GL_ELEMENT_ARRAY_BUFFER, 1, sizeof(indices), indices, GL_STATIC_DRAW);
	buffer_bind(ib->type, ib->buffer);

	char* pv = shader_file_parse("src/block_vert.glsl");
	char* pf = shader_file_parse("src/block_frag.glsl");

	shader = shader_create(pv, pf);
}

void block_create(Block* b, Vec2f pos, U32 id)
{
	b->pos = pos;
	b->id = id;
}


void block_tick(Vec2f* pos, U32 id, Block* matrix, U32 matrix_width, U32 matrix_height)
{
	if(pos->y<matrix_height-1)
		pos->y+=1;
}

void block_render(Vec2f pos, U32 id)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 mvp(1.0f);

	glBindVertexArray(vao);
	buffer_bind(vb->type, vb->buffer);
	buffer_bind(ib->type, ib->buffer);

	glUseProgram(shader);

	Global_Data* g_d = global_get();

	view = glm::translate(view, glm::vec3(((pos.x-(g_d->window_width/2))+size.x/2)+(pos.x*size.x),
	((pos.y+(g_d->window_height/2))-size.y/2)-(pos.y*size.y),0.0f));

	model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));

	mvp = global_get()->projection * view * model;
	
	shader_uniform_set_mat4(shader, "u_mvp", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}