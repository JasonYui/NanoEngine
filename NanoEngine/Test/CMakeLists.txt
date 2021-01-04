set(SRC_LIST)

file(GLOB_RECURSE 
    SRC_LIST 
    *.hpp
    *.inl
    *.cpp
)

set(SRC_FILES ${SRC_LIST})

set(GTEST_DEBUG_LIST)
set(GTEST_RELEASE_LIST)

file(GLOB_RECURSE 
    GTEST_DEBUG_LIST 
    ${ENGINE_THIRD_PARTIES_PATH}/GTest/Lib/Debug/*.lib
)

file(GLOB_RECURSE 
    GTEST_RELEASE_LIST 
    ${ENGINE_THIRD_PARTIES_PATH}/GTest/Lib/Release/*.lib
)

set(GTEST_DEBUG ${GTEST_DEBUG_LIST})
set(GTEST_RELEASE ${GTEST_RELEASE_LIST})


add_executable (EngineTest ${SRC_FILES})

include_directories("${ENGINE_THIRD_PARTIES_PATH}/GTest/Include/")

target_link_libraries(EngineTest 
    Common
    Client
    debug ${GTEST_DEBUG}
    optimized ${GTEST_RELEASE}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})