aux_source_directory(. DIR_SRCS)

add_executable(TestGame GameMain.cpp)

target_link_libraries(TestGame Client)
