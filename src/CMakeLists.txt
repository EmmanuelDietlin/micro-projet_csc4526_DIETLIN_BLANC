
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}    "SeagullEvent.h")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC sfml-graphics imgui-sfml)
