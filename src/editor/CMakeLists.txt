add_library(bp_editor STATIC application.cpp scene_manager.cpp undo_redo.cpp)
target_include_directories(bp_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(bp_editor PUBLIC bp_core bp_graphics bp_ui bp_modeling)
