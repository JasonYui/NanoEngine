cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_ABSOLUTE_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../)
set(ENGINE_THIRD_PARTIES_PATH ${PROJECT_ABSOLUTE_SOURCE_DIR}NanoEngine/ThirdParties)
message(${ENGINE_THIRD_PARTIES_PATH})

project(Game)

include_directories("${PROJECT_SOURCE_DIR}/")

add_subdirectory(NanoEngine)
add_subdirectory(Game)