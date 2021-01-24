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

list(FILTER SRC_LIST EXCLUDE REGEX "Thread+" )

set(SRC_FILES ${SRC_LIST})

set(CROSSGUID_DEBUG ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Debug/crossguid-dgb.lib)
set(CROSSGUID_RELEASE ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Release/crossguid.lib)
set(SPDLOG_RELEASE ${ENGINE_THIRD_PARTIES_PATH}/Spdlog/Lib/Release/spdlog.lib)

if(MONO_CLR)
    set(MONO ${MONO_PATH}/lib/mono-2.0-sgen.lib)
else()
    set(MONO)
endif()

add_library (Common ${SRC_FILES})

target_link_libraries(Common 
    debug ${CROSSGUID_DEBUG}
    optimized ${CROSSGUID_RELEASE}
    ${MONO}
    ${SPDLOG_RELEASE}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})