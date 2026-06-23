add_library(bp_graphics STATIC renderer.cpp camera.cpp mesh_buffer.cpp shader.cpp viewport.cpp)
target_include_directories(bp_graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(bp_graphics PUBLIC bp_core OpenGL::OpenGL glfw glm::glm Vulkan::Vulkan)
