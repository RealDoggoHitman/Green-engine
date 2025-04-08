// ImGuiWindows.h
#ifndef IMGUI_WINDOWS_H
#define IMGUI_WINDOWS_H

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>
#include <string>
#include <filesystem>
#include <fstream>

#include "Lua.h"
#include "TextEditor.h"

Lua luaCode;

void DrawImguiWindows(); // Only declaration, no definition

#endif // IMGUI_WINDOWS_H
