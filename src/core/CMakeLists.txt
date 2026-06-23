add_library(bp_core STATIC logger.cpp math_utils.cpp allocator.cpp)
target_include_directories(bp_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(bp_core PUBLIC spdlog::spdlog glm::glm)
