
add_library(imgui "imgui.cpp" "imgui_widgets.cpp" "imgui_draw.cpp" "imgui_tables.cpp")
target_include_directories(imgui PUBLIC ./)

target_link_libraries(imgui PUBLIC sfml-graphics)
