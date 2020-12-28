set(SRC_LIST)

file(GLOB_RECURSE 
    SRC_LIST 
    *.hpp
    *.cpp
)

set(SRC_FILES ${SRC_LIST})

add_executable(TestGame ${SRC_FILES})

target_link_libraries(TestGame Client)
#target_link_libraries(TestGame GameCS)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})