add_library(bp_modeling STATIC mesh.cpp mesh_operations.cpp scene.cpp)
target_include_directories(bp_modeling PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(bp_modeling PUBLIC bp_core glm::glm)
