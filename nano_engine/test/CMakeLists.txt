set(PROJECT_NAME UnitTest)

# collect file
set(SRC_LIST)

file(GLOB_RECURSE 
    SRC_LIST 
    *.hpp
    *.inl
    *.cpp
)

set(SRC_FILES ${SRC_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})

# dependence 3rd

set(CONAN_PKGS
    gtest/1.10.0
)

conan_cmake_run(REQUIRES ${CONAN_PKGS}
    BUILD missing
    CONFIGURATION_TYPES "Release;Debug"
    INSTALL_ARGS "-r=conan-center"
)

include(${CMAKE_BINARY_DIR}/NanoEngine/Test/conanbuildinfo.cmake)
conan_basic_setup()


#set(GTEST_DEBUG_LIST)
#set(GTEST_RELEASE_LIST)

#file(GLOB_RECURSE 
#    GTEST_DEBUG_LIST 
#    ${ENGINE_THIRD_PARTIES_PATH}/GTest/Lib/Debug/*.lib
#)

#file(GLOB_RECURSE 
#    GTEST_RELEASE_LIST 
#    ${ENGINE_THIRD_PARTIES_PATH}/GTest/Lib/Release/*.lib
#)

#set(GTEST_DEBUG ${GTEST_DEBUG_LIST})
#set(GTEST_RELEASE ${GTEST_RELEASE_LIST})

add_executable (${PROJECT_NAME} ${SRC_FILES})

target_link_directories(${PROJECT_NAME} PRIVATE ${CONAN_LIB_DIRS_DEBUG} PRIVATE ${CONAN_LIB_DIRS_RELEASE})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CONAN_INCLUDE_DIRS}
)

#target_link_libraries(${PROJECT_NAME} 
#    debug ${CONAN_LIBS_DEBUG}
#    optimized ${CONAN_LIBS}
#)

#include_directories("${ENGINE_THIRD_PARTIES_PATH}/GTest/Include/")

target_link_libraries(${PROJECT_NAME} 
    Common
    Client
    debug ${CONAN_LIBS_DEBUG}
    optimized ${CONAN_LIBS_RELEASE}
)