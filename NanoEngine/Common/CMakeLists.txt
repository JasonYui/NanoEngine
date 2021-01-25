set(PROJECT_NAME Common)

# collect file
set(SRC_LIST)

file(GLOB_RECURSE 
    SRC_LIST 
    *.hpp
    *.inl
    *.cpp
)

if(NOT MONO_CLR)
    list(FILTER SRC_LIST EXCLUDE REGEX "CSDelegate+" )
endif()

# unfinished
list(FILTER SRC_LIST EXCLUDE REGEX "Thread+" )

set(SRC_FILES ${SRC_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
# dependence 3rd
set(CONAN_PKGS
    spdlog/1.8.2
    nameof/0.10.0
)

conan_cmake_run(REQUIRES ${CONAN_PKGS}
    BUILD missing
    CONFIGURATION_TYPES "Release;Debug"
    INSTALL_ARGS "-r=conan-center"
)

include(${CMAKE_BINARY_DIR}/NanoEngine/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

#set(CROSSGUID_DEBUG ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Debug/crossguid-dgb.lib)
#set(CROSSGUID_RELEASE ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Release/crossguid.lib)
#set(SPDLOG_RELEASE ${ENGINE_THIRD_PARTIES_PATH}/Spdlog/Lib/Release/spdlog.lib)

#if(MONO_CLR)
#    set(MONO ${MONO_PATH}/lib/mono-2.0-sgen.lib)
#else()
#    set(MONO)
#endif()

add_library (${PROJECT_NAME} ${SRC_FILES})

target_link_directories(${PROJECT_NAME} PUBLIC ${CONAN_LIB_DIRS_DEBUG} PUBLIC ${CONAN_LIB_DIRS_RELEASE})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CONAN_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    debug ${CONAN_LIBS_DEBUG}
    optimized ${CONAN_LIBS}
)

#target_link_libraries(Common 
    #debug ${CROSSGUID_DEBUG}
    #optimized ${CROSSGUID_RELEASE}
    #${MONO}
    #${SPDLOG_RELEASE}
#)