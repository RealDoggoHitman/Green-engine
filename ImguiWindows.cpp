// ImGuiWindows.cpp
#include "ImguiWindows.h"

namespace fs = std::filesystem;

void DrawImguiWindows()
{
    // === FPS Window ===
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

    // === Lua Script Text Editor ===
    {
        static TextEditor editor;
        static bool initialized = false;
        static std::vector<std::string> luaFiles;
        static int selectedFileIndex = -1;
        static std::string currentFilePath;

        static char newFileNameBuffer[128] = "NewScript.lua";
        static bool openNewFilePopup = false;

        // Load .lua file list
        auto RefreshLuaFiles = [&]() {
            luaFiles.clear();
            for (const auto& entry : fs::directory_iterator("LuaScripts"))
            {
                if (entry.path().extension() == ".lua")
                {
                    luaFiles.push_back(entry.path().filename().string());
                }
            }
            };

        if (!initialized)
        {
            editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
            RefreshLuaFiles();
            initialized = true;
        }

        ImGui::Begin("Code Editor");

        // Top controls: Add + Refresh
        if (ImGui::Button("+ Add New File"))
        {
            openNewFilePopup = true;
            ImGui::OpenPopup("Create New Lua File");
        }

        if (openNewFilePopup)
        {
            ImGui::SetNextWindowSize(ImVec2(350, 120));
            if (ImGui::BeginPopupModal("Create New Lua File", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::InputText("File Name", newFileNameBuffer, IM_ARRAYSIZE(newFileNameBuffer));

                if (ImGui::Button("Create"))
                {
                    std::string newFilePath = "LuaScripts/" + std::string(newFileNameBuffer);

                    if (!fs::exists(newFilePath))
                    {
                        std::ofstream file(newFilePath);
                        file << "-- New Lua script\n";
                        file.close();
                        RefreshLuaFiles();
                        openNewFilePopup = false;
                        ImGui::CloseCurrentPopup();
                    }
                    else
                    {
                        ImGui::TextColored(ImVec4(1, 0, 0, 1), "File already exists!");
                    }
                }

                ImGui::SameLine();

                if (ImGui::Button("Cancel"))
                {
                    openNewFilePopup = false;
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Refresh"))
        {
            RefreshLuaFiles();
        }

        ImGui::Separator();

        if (!luaFiles.empty())
        {
            const char* preview = selectedFileIndex >= 0 ? luaFiles[selectedFileIndex].c_str() : "Select Lua File";

            if (ImGui::BeginCombo("Lua Files", preview))
            {
                for (int i = 0; i < luaFiles.size(); ++i)
                {
                    bool isSelected = (i == selectedFileIndex);
                    if (ImGui::Selectable(luaFiles[i].c_str(), isSelected))
                    {
                        selectedFileIndex = i;
                        currentFilePath = "LuaScripts/" + luaFiles[i];

                        // Load file content
                        std::ifstream file(currentFilePath);
                        if (file)
                        {
                            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                            editor.SetText(content);
                        }
                    }
                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            editor.Render("TextEditor");

            if (ImGui::Button("Save") && selectedFileIndex >= 0)
            {
                std::ofstream file(currentFilePath);
                if (file)
                {
                    file << editor.GetText();
                    file.close();

                    luaCode.InitLua();
                }
            }
        }
        else
        {
            ImGui::Text("No .lua files found in LuaScripts directory.");
        }

        ImGui::End();
    }
}