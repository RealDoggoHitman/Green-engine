// ImGuiWindows.cpp
#include "ImguiWindows.h"

void DrawImguiWindows()
{
     // FPS Window
    {
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.3f);  // Transparent background

        ImGui::Begin("Performance", nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse);

        float fps = ImGui::GetIO().Framerate;
        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Frame Time: %.3f ms", 1000.0f / fps);

        ImGui::End();
    }
    // Text Editor
    {

    }
}
