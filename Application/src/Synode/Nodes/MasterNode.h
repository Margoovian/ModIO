#pragma once

#include <ImNodeFlow.h>
#include <ModIO.h>

class MasterNode : public ImFlow::BaseNode
{

public:
    MasterNode()
    {
        setTitle("Master");
        setStyle(ImFlow::NodeStyle::red());
        ImFlow::BaseNode::addIN<ModIO::Transports::Signal>("Audio In", ModIO::Transports::Signal(), ImFlow::ConnectionFilter::SameType(), ImFlow::PinStyle::cyan());
    }

    void draw() override
    {
        ImGui::SetNextItemWidth(500.f);


        if (ImGui::Button("Test"))
        {
            std::cout << ImFlow::BaseNode::getName() << '\n';
        }
    }

};