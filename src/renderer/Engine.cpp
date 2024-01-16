#include <glad/glad.h>
#include "Engine.h"
#include "Shader.h"
#include "../mesh/TriangleMesh.h"
#include <chrono>

#include <spdlog/spdlog.h>

Engine::Engine()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->isRunning = true;
    this->programTime = 0;
    this->deltaTime = 0;
    this->window = glfwCreateWindow(800, 600, "hewwo", nullptr, nullptr);
    this->timeStart = clock::now();
    if (this->window == nullptr)
    {
        spdlog::critical("Could not create GLFW window");
        glfwTerminate();
        isRunning = false;
    }
    glfwMakeContextCurrent(this->window);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) // NOLINT(clang-diagnostic-cast-function-type-strict)
    {
        spdlog::critical("Could not load GLAD");
        isRunning = false;
    }
    this->shaders.quadShader = Shader("resources/shaders/cubes.vert", "resources/shaders/cubes.frag");
}



void Engine::update()
{
    this->programTime = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - this->timeStart).count();
}

void Engine::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    this->shaders.quadShader.use();

    for (auto& quad : quads)
    {
        quad.bindVertexObjects();
        quad.draw();
        quad.unbindVertexObjects();
    }
    //this->shaders.quadShader.done();
}

void Engine::init()
{
    this->quads.emplace_back(TriangleMesh());
    for (auto& quad: quads)
    {
        quad.setVertexObjects();
    }
}

void Engine::handleEvents()
{
    
}

void Engine::run()
{
    this->init();
    while(isRunning && !glfwWindowShouldClose(this->window))
    {
        handleEvents();
        update();
        render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
    for (auto& quad : quads)
    {
        quad.unbindVertexObjects();
        quad.destroyVertexObjects();
    }
    this->shaders.quadShader.destroy();
    glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}