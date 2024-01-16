cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME oglvoxel)
set(CMAKE_CXX_STANDARD 20)

include_directories(includes)

# spdlog
add_subdirectory(external/spdlog)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLAD
set(GLAD_PATH includes/glad)
add_library(glad STATIC ${GLAD_PATH}/glad.c)

# glm
add_subdirectory(external/glm)

# stb_image
set(STB_IMAGE_PATH includes/stb_image)
file(GLOB STB_IMAGE_SOURCES ${STB_IMAGE_PATH}/*.c)
add_library(stb_image STATIC ${STB_IMAGE_SOURCES})

file(GLOB top_level src/*.cpp)
file(GLOB renderer src/renderer/*.cpp)
file(GLOB mesh src/mesh/*.cpp)
list(APPEND EXEC_SOURCES ${top_level} ${renderer} ${mesh})

file(GLOB renderer src/renderer/*.h)
file(GLOB mesh src/mesh/*.h)
list(APPEND EXEC_HEADERS ${renderer} ${mesh} ${types})

add_executable(${PROJECT_NAME} ${EXEC_SOURCES} ${EXEC_HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC
	glad
	glfw
	glm::glm
	stb_image
	spdlog::spdlog
)

