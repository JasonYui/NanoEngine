set(ALL_FILES)

file(GLOB_RECURSE ALL_FILES ./*.*)
list(APPEND FILE_LIST ${ALL_FILES})

add_executable(Premake ${FILE_LIST})

set(LIB_CLANG ${LLVM_PATH}/lib/libclang.lib)

target_link_libraries(Premake 
    ${LIB_CLANG}
)