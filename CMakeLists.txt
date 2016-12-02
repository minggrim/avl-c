project(ezavl)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -D__USE_UNIX98 -std=gnu99 -Wall -Werror -Wno-unused-variable -Wno-unused-but-set-variable -pthread")

add_library(ezavl avl.c)
add_executable(example example.c)
target_link_libraries(example ezavl)
