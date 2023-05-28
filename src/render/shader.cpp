#include "shader.h"
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string>

#pragma warning(disable : 4996)

char* shader_file_parse(const char* file_source)
{
    std::string text_final;

    std::ifstream file(file_source);

    std::string text;
    while (std::getline(file, text))
    {
        text += '\n';
        text_final += text;
    }

    std::cout << "After file read\n\n" << text_final << "Ending\n\n";

    char* string = (char*)malloc(sizeof(char) * text_final.length());
    strcpy(string, text_final.c_str());

    return string;
}

U32 shader_compile(U32 type, const char* source)
{
    //compiled
    U32 id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);


    //error check
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "[ERROR] FAILED TO COMPILE SHADER\n";
        std::cout << message << std::endl;
        glDeleteShader(0);

        return 0;
    }

    return id;
}

U32 shader_create(const char* shader_vert, const char* shader_frag)
{
    U32 program = glCreateProgram();
    U32 vs = shader_compile(GL_VERTEX_SHADER, shader_vert);
    U32 fs = shader_compile(GL_FRAGMENT_SHADER, shader_frag);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void shader_uniform_set_mat4(U32 shader, const char* name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void shader_uniform_set_vec3(U32 shader, const char* name, glm::vec3 vec)
{
    glUniform3fv(glGetUniformLocation(shader, name), 1, glm::value_ptr(vec));
}
