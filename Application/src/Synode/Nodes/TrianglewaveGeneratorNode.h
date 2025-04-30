#pragma once

#include <ImNodeFlow.h>
#include <imgui-knobs.h>
#include <Signal.h>
#include <ModIO.h>

class TrianglewaveGeneratorNode : public ImFlow::BaseNode
{

public:
    TrianglewaveGeneratorNode()
    {

        m_Generator = std::make_unique<ModIO::Generators::TrianglewaveGenerator>();

        m_Generator->mFrequency = m_Frequency;
        m_Generator->mAmplitude = m_Volume * 0.01f;

        setTitle("Triangle Wave Generator");
        setStyle(ImFlow::NodeStyle::brown());
        ImFlow::BaseNode::addOUT< ModIO::Interfaces::AudioGeneratorInterface*>("Audio Out", ImFlow::PinStyle::brown())->behaviour([this]() { return m_Generator.get(); });
    }

    void draw() override
    {
        ImGui::SetNextItemWidth(500.f);



        if (ImGuiKnobs::Knob("Frequency", &m_Frequency, 32.0f, 523.0f, 0.1f, "%.1f freq", ImGuiKnobVariant_WiperDot)) {
            m_Generator->mFrequency = m_Frequency;
        }
        if (ImGuiKnobs::Knob("Volume", &m_Volume, 0.0f, 100.0f, 0.1f, "%.1f pc", ImGuiKnobVariant_WiperDot)) {
            m_Generator->mAmplitude = m_Volume * 0.01f;
        }
    }

private:
    ModIO::TD::UniqueTrianglewaveGenerator m_Generator;
    float m_Frequency = 32.0f;
    float m_Volume = 50.0f;
};