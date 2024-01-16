#pragma once
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "../mesh/TriangleMesh.h"

#include <chrono>
#include <vector>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
class Engine
{
public:
    using clock = std::chrono::high_resolution_clock;

    GLFWwindow* window;

    bool isRunning;
    long long programTime;
    long long deltaTime;
    std::chrono::time_point<std::chrono::steady_clock> timeStart;
    std::vector<TriangleMesh> quads;
    Shaders shaders = Shaders();

    Engine();
    void update();
    void render();
    void init();
    static void handleEvents();



    void run();
};


