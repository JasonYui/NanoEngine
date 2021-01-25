cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)


set(PROJECT_ABSOLUTE_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../)
set(ENGINE_THIRD_PARTIES_PATH ${PROJECT_ABSOLUTE_SOURCE_DIR}NanoEngine/ThirdParties)
set(LLVM_PATH C:/Code/LLVM)
set(MONO_PATH $ENV{ProgramFiles}/Mono)

include(${PROJECT_ABSOLUTE_SOURCE_DIR}/Conan/conan.cmake)

project(Game)

include_directories("${PROJECT_SOURCE_DIR}/")
include_directories("${PROJECT_SOURCE_DIR}/NanoEngine/")
include_directories("${LLVM_PATH}/include/")
if(MONO_CLR)
    include_directories("${MONO_PATH}/include/mono-2.0/")
endif()

add_subdirectory(NanoEngine)
add_subdirectory(Game)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)