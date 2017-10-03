cmake_minimum_required(VERSION 3.9)
project(autofetch CXX)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( Threads REQUIRED )

add_executable(autofetch main.cpp)
target_link_libraries(autofetch ${CMAKE_THREAD_LIBS_INIT})
