#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "global.h"
#include "shader.h"
#include "world.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const U32 SCR_WIDTH = 800;
const U32 SCR_HEIGHT = 800;

float aspect = SCR_WIDTH / SCR_HEIGHT;
float half_height = SCR_HEIGHT / 2;
float half_width = half_height * aspect;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //getting world size==============|
    //TODO: add error checking
    U32 world_width, world_height;

    printf("Enter world width: ");
    std::cin>>world_width;

    printf("Enter world height: ");
    std::cin>>world_height;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    global_get()->window = window;
    global_get()->window_width = SCR_WIDTH;
    global_get()->window_height = SCR_HEIGHT;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-half_width, half_width, -half_height, half_height, 0.0001f, 3000.f);
	global_get()->projection = projection;

    //init=======================================|
    World world = World{};
    world_init(&world,world_width,world_height);

    block_init(SCR_WIDTH/world_width, SCR_HEIGHT/world_height);   
    world_create_block(world.matrix,world.width,0,0,0);   
    Block* b = world_get_block(world.matrix,world.width,0,0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1, 0.3, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
 
        block_render(b->pos,b->id);
        block_tick(&b->pos,b->id,world.matrix,world.width,world.height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    world_release(&world);
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}