set(ALL_FILES)

file(GLOB_RECURSE ALL_FILES ./*.*)
list(APPEND FILE_LIST ${ALL_FILES})

add_library (Common ${FILE_LIST})

set(CROSSGUID_DEBUG ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Debug/crossguid-dgb.lib)
set(CROSSGUID_RELEASE ${ENGINE_THIRD_PARTIES_PATH}/CrossGuid/Lib/Release/crossguid.lib)

target_link_libraries(Common 
    debug ${CROSSGUID_DEBUG}
    optimized ${CROSSGUID_RELEASE}
)