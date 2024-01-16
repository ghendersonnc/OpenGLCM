#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
class Shader {
public:
    GLint ID;
    bool shaderProgramFailure = false;
    Shader() = default;
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void test();
    void use();
    void setFloat(const GLchar* name, float value, bool useShader = false);
    void setInteger(const GLchar* name, int value, bool useShader = false);
    void setVector2f(const GLchar* name, float x, float y, bool useShader = false);
    void setVector2f(const GLchar* name, const glm::vec2& vec, bool useShader = false);
    void setVector3f(const GLchar* name, float x, float y, float z, bool useShader = false);
    void setVector3f(const GLchar* name, const glm::vec3& vec, bool useShader = false);
    void setVector4f(const GLchar* name, float x, float y, float z, float w, bool useShader = false);
    void setVector4f(const GLchar* name, const glm::vec4& vec, bool useShader = false);
    void setMatrix4(const GLchar* name, const glm::mat4& matrix, bool useShader = false);
    void destroy();

    void update();
private:
    static std::string _readShaderFile(const std::string& filePath);
};

struct Shaders
{
    Shader quadShader;
};