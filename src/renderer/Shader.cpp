#include <glad/glad.h>
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    /*
     * I do not know why but doing _readShaderFile(shaderPath).c_str() does not work
     */
    auto temporaryString = _readShaderFile(vertexShaderPath);
    auto shaderCode = temporaryString.c_str();
    glShaderSource(vertexShader, 1, &shaderCode, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        spdlog::critical("COULD NOT COMPILE VERTEX SHADER :: {}", infoLog);
        this->shaderProgramFailure = true;
    }
    const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    temporaryString = _readShaderFile(fragmentShaderPath);
    shaderCode = temporaryString.c_str();
    glShaderSource(fragmentShader, 1, &shaderCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        spdlog::critical("COULD NOT COMPILE FRAGMENT SHADER :: {}", infoLog);
        this->shaderProgramFailure = true;

    }

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->ID, 512, nullptr, infoLog);
        spdlog::critical("COULD NOT CREATE SHADER PROGRAM :: {}", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::test()
{
    spdlog::info(this->ID);
}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::setFloat(const GLchar* name, const float value, const bool useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setInteger(const GLchar* name, const int value, const bool useShader)
{
    if (useShader)
        this->use();

    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector2f(const GLchar* name, const float x, const float y, const bool useShader)
{
    if (useShader)
        this->use();

    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::setVector2f(const GLchar* name, const glm::vec2& vec, const bool useShader)
{
    if (useShader)
        this->use();

    glUniform2f(glGetUniformLocation(this->ID, name), vec.x, vec.y);
}

void Shader::setVector3f(const GLchar* name, const float x, const float y, const float z, const bool useShader) 
{
    if (useShader)
        this->use();

    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::setVector3f(const GLchar* name, const glm::vec3& vec, const bool useShader) 
{
    if (useShader)
        this->use();

    glUniform3f(glGetUniformLocation(this->ID, name), vec.x, vec.y, vec.z);
}

void Shader::setVector4f(const GLchar* name, const float x, const float y, const float z, const float w, const bool useShader) 
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name),x,y,z,w);
}

void Shader::setVector4f(const GLchar* name, const glm::vec4& vec, const bool useShader) 
{
    if (useShader)
        this->use();

    glUniform4f(glGetUniformLocation(this->ID, name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMatrix4(const GLchar* name, const glm::mat4& matrix, const bool useShader) 
{
    if (useShader)
        this->use();

    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::destroy()
{
    glDeleteShader(this->ID);
}

void Shader::update()
{
}

std::string Shader::_readShaderFile(const std::string& filePath)
{
    const std::ifstream shaderFile(filePath);
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}
