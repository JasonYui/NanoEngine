set(PROJECT_NAME Client)
set(SRC_LIST)

file(GLOB_RECURSE 
    SRC_LIST 
    *.hpp
    *.inl
    *.cpp
)

set(SRC_FILES ${SRC_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
add_library (${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} Common)