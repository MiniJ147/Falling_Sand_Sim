#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils.h"
#include <GLFW/glfw3.h>

struct Global_Data
{	
	glm::mat4 projection;
	GLFWwindow* window;
	U32 window_width;
	U32 window_height;
};

static Global_Data g_d = {};

inline Global_Data* global_get()
{
	return &g_d;
}