#include <spdlog/spdlog.h>
#include "renderer/Engine.h"
#include <windows.h>
#include <chrono>


int main()
{
#ifndef _WIN32
    spdlog::critical("kys");
    return 1;
#endif
    spdlog::info("Yay :D!");

    Engine engine;
    engine.run();
}