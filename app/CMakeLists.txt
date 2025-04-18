file(GLOB SOURCES "*.cpp")

add_executable(RBTreeApp ${SOURCES})

target_link_libraries(RBTreeApp PRIVATE Qt5::Core Qt5::Widgets)
