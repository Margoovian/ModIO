#pragma once

#include <ImNodeFlow.h>
#include <imgui-knobs.h>
#include <Signal.h>
#include <ModIO.h>

class GeneratorNode : public ImFlow::BaseNode
{

public:
    GeneratorNode()
    {
        setTitle("Generator");
        setStyle(ImFlow::NodeStyle::green());
        ImFlow::BaseNode::addIN< ModIO::Interfaces::AudioGeneratorInterface*>("Generator Type", nullptr, ImFlow::ConnectionFilter::SameType(), ImFlow::PinStyle::brown());
        ImFlow::BaseNode::addOUT<ModIO::Transports::Signal>("Audio Out", ImFlow::PinStyle::cyan())->behaviour([this]() { return getInVal< ModIO::Interfaces::AudioGeneratorInterface*>("Generator Type")->Generate(); });
    }

    void draw() override
    {
        ImGui::SetNextItemWidth(500.f);


        if (ImGui::Button("Hello"))
        {
            std::cout << "Hello!" << '\n';
        }
    }
};