cmake_minimum_required(VERSION 3.20)
project(BlenderPro VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BP_BUILD_TESTS "Build tests" ON)
option(BP_WITH_CUDA "Build with CUDA support" OFF)
option(BP_WITH_OPTIX "Build with OptiX support" OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory(src/core)
add_subdirectory(src/graphics)
add_subdirectory(src/ui)
add_subdirectory(src/modeling)
add_subdirectory(src/editor)

add_executable(blender-pro src/main.cpp)

target_link_libraries(blender-pro
    bp_core bp_graphics bp_ui bp_modeling bp_editor
    OpenGL::OpenGL glfw glm::glm nlohmann_json::nlohmann_json spdlog::spdlog
)

if(BP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
