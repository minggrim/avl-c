project(ezavl)
add_library(ezavl avl.c)
add_executable(example example.c)
target_link_libraries(example ezavl)
