cmake_minimum_required(VERSION 3.12)
project(RBTreeVisualization)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


#add_compile_definitions(FORCE_ASSERT)

add_subdirectory(app)
