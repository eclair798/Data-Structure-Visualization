file(GLOB SOURCES "*.cpp")

add_executable(App ${SOURCES})
target_link_libraries(App Qt5::Core)
