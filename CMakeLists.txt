# Minimum CMake version and project
cmake_minimum_required(VERSION 3.16)
project(mini_shell)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


# Source sets
add_library(mini_shell_lib
	src/builtins.c
	src/parser.c
	src/shell.c
	src/utils.c
)
target_include_directories(mini_shell_lib PUBLIC include)


# Executable
add_executable(mini_shell src/main.c)
target_link_libraries(mini_shell PRIVATE mini_shell_lib)

# Compiler warnings
target_compile_options(mini_shell_lib PRIVATE -Wall -Wextra)
target_compile_options(mini_shell PRIVATE -Wall -Wextra)

add_executable(unit_tests 
    tests/run_all_tests.c
    tests/test_builtins.c
    tests/test_parser.c
)
target_link_libraries(unit_tests PRIVATE mini_shell_lib)
