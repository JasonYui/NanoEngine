set(SRC_LIST)

file(GLOB_RECURSE 
    SRC_LIST 
    *.hpp
    *.inl
    *.cpp
    ./*.hpp
    ./*.inl
    ./*.cpp
)

set(SRC_FILES ${SRC_LIST})

add_library (Client ${SRC_LIST})

target_link_libraries(Client Common)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})