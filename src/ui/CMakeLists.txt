add_library(bp_ui STATIC ui_manager.cpp panels/outliner.cpp panels/properties.cpp panels/viewport.cpp)
target_include_directories(bp_ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(bp_ui PUBLIC bp_core bp_graphics)
