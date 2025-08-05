file(GLOB SOURCES "*.cpp")

add_executable(RBTree ${SOURCES})

target_link_libraries(RBTree PRIVATE Qt5::Core Qt5::Widgets)
