cmake_minimum_required(VERSION 3.15)
project(growable-buf)

#       Compile library and tester exe with coverage included

# Alternative ways to do the same thing:
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror -O3 -g3")
# set_property(TARGET growbuf PROPERTY C_STANDARD 99)
set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -O0 -g -fprofile-arcs -ftest-coverage)

set(SOURCES buf.c)
set(HEADERS buf.h)
add_library(growbuf ${SOURCES} ${HEADERS})

add_executable(growbuf_test buf.h tests.c)
target_link_libraries(growbuf_test growbuf gcov)

#       Test with tester exe via cmd args

include(CTest)
enable_testing()
add_test(NAME "test_initialization" COMMAND "$<TARGET_FILE:growbuf_test>" 1 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "test_push" COMMAND "$<TARGET_FILE:growbuf_test>" 2 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "test_grow" COMMAND "$<TARGET_FILE:growbuf_test>" 3 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "test_pop" COMMAND "$<TARGET_FILE:growbuf_test>" 4 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME "test_mem_alloc_failure" COMMAND "$<TARGET_FILE:growbuf_test>" 5 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
