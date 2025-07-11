cmake_minimum_required(VERSION 3.10)
project(mini_shell)

set(CMAKE_C_STANDARD 99)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(mini_shell
    src/main.c
    src/shell.c
)