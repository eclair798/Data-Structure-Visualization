cmake_minimum_required(VERSION 3.16)
project(RBTreeVisualization)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

#add_compile_definitions(FORCE_ASSERT)

add_subdirectory(app)
