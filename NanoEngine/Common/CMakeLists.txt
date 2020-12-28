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

add_library (Common ${SRC_FILES})

set(CROSSGUID_DEBUG ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Debug/crossguid-dgb.lib)
set(CROSSGUID_RELEASE ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Release/crossguid.lib)

if(MONO_CLR)
    set(MONO ${MONO_PATH}/lib/mono-2.0-sgen.lib)
else()
    set(MONO)
endif()

target_link_libraries(Common 
    debug ${CROSSGUID_DEBUG}
    optimized ${CROSSGUID_RELEASE}
    ${MONO}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})