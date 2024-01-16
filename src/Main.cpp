#include <spdlog/spdlog.h>
#include "renderer/Engine.h"

int main()
{
#ifndef _WIN32
    spdlog::critical("Only Windows is supported");
    return 1;
#endif
    spdlog::info("Yay :D!");

    Engine engine;
    engine.run();
}
