cmake_minimum_required (VERSION 3.8)

project("Vulkan")

add_executable (Vulkan "main.cpp")

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Vulkan PRIVATE imgui::imgui)
