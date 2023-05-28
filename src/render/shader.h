#pragma once
#include "../utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

char* shader_file_parse(const char* file_source);

U32 shader_compile(U32 type, const char* source);
U32 shader_create(const char* shader_vert, const char* shader_frag);

void shader_uniform_set_mat4(U32 shader, const char* name, glm::mat4 matrix);
void shader_uniform_set_vec3(U32 shader, const char* name, glm::vec3 vec);