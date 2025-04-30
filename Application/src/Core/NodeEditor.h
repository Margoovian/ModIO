#pragma once

#include <ImNodeFlow.h>
#include <imgui-knobs.h>

// From https://github.com/Fattorino/ImNodeFlow/blob/master/example/example.hpp

/* Node editor that sets up the grid to place nodes */
struct NodeEditor : ImFlow::BaseNode
{

    ImFlow::ImNodeFlow Handler;

    NodeEditor(float d, std::size_t r)
        : BaseNode()
    {
        
    }

    void SetSize(ImVec2 d)
    {
        Handler.setSize(d);
    }

    void draw() override
    {
        Handler.update();
    }

    void DrawGrid() 
    {

        ImGuiIO& io = ImGui::GetIO();

        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::SetNextWindowPos(ImVec2(1, 1));

        const ImVec2 editorSize = io.DisplaySize - ImVec2(16, 16);
        ImGui::Begin("Node Editor", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        SetSize(editorSize);
        draw();
        ImGui::End();
    }
};