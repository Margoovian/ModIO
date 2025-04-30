#include "Synode.h"

#include "Nodes/GeneratorNode.h"
#include "Nodes/MasterNode.h"
#include "Nodes/SineGeneratorNode.h"
#include "Nodes/SquarewaveGeneratorNode.h"
#include "Nodes/TrianglewaveGeneratorNode.h"
#include "Nodes/SawtoothGeneratorNode.h"

void Synode::Render()
{
	m_NodeEditor->DrawGrid();
}

void Synode::Process()
{
}

void Synode::Shutdown()
{
	if (m_Session && m_Session->IsRunning())
	{
		m_Session->Stop();
	}
}

void Synode::SetupApp()
{

	InitializeGraph();

	m_MasterNode = m_NodeEditor->Handler.addNode<MasterNode>({ 900,100 });
	m_NodeEditor->Handler.addNode<GeneratorNode>({ 500,100 });
	m_NodeEditor->Handler.addNode<SineGeneratorNode>({ 200,100 });
	m_NodeEditor->Handler.addNode<SquarewaveGeneratorNode>({ 200,350 });
	m_NodeEditor->Handler.addNode<TrianglewaveGeneratorNode>({ 200,600 });
	m_NodeEditor->Handler.addNode<SawtoothGeneratorNode>({ 200,850 });

	InitializeAudio();

}

void Synode::InitializeAudio()
{
	using namespace ModIO;

	m_Session = ModIO::CreateSession();

	GetSessionInterface()->SetGraphEvaluationFunction(std::bind(&Synode::ProcessAudioGraph, this));

	m_Session->Start();

}

void Synode::InitializeGraph()
{
	m_NodeEditor = std::make_unique<NodeEditor>(1280-16, 720-16);
}

const ModIO::Transports::Signal* Synode::ProcessAudioGraph()
{
	return &m_MasterNode->getInVal<ModIO::Transports::Signal>("Audio In");
}
