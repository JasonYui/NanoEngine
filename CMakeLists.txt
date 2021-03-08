cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)


set(PROJECT_ABSOLUTE_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../)
set(ENGINE_THIRD_PARTIES_PATH ${PROJECT_ABSOLUTE_SOURCE_DIR}nano_engine/third_parties)
set(LLVM_PATH C:/Code/LLVM)
set(MONO_PATH $ENV{ProgramFiles}/Mono)

include(${PROJECT_ABSOLUTE_SOURCE_DIR}/conan/conan.cmake)

project(Game)

include_directories("${PROJECT_SOURCE_DIR}/")
include_directories("${PROJECT_SOURCE_DIR}/nano_engine/")
include_directories("${LLVM_PATH}/include/")
if(MONO_CLR)
    include_directories("${MONO_PATH}/include/mono-2.0/")
endif()

add_subdirectory(nano_engine)
add_subdirectory(game)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)