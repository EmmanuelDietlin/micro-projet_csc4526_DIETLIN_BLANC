
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}  "Circle.h" "Circle.cpp" "Group.h" "Group.cpp" "Shape.h" "Shape.cpp")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC pugixml sfml-graphics imgui-sfml)
