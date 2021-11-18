cmake_minimum_required(VERSION 3.0)
project(esub)
add_executable(esub esub.c)
add_compile_options(-Wall -Wextra -pedantic -Werror)

enable_testing()
add_test(TestBasicReplace ./test.sh find replace "find and replace")
add_test(TestDigits ./test.sh "[0-9]+" "X" "I have reached 255.255.255.255 yesterday")
add_test(NAME TestGroups COMMAND ./test.sh "(abc)(def)(ghi)" "\\3\\2\\1" "startabcdefghiend")