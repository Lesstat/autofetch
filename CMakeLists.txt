cmake_minimum_required(VERSION 3.9)
project(autofetch)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(autofetch main.cpp)
