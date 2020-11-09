set(ALL_FILES)

file(GLOB_RECURSE ALL_FILES ./*.*)
list(APPEND FILE_LIST ${ALL_FILES})

add_library (Common ${FILE_LIST})