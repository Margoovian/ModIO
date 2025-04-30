#pragma once

#include <Core/App.h>
#include <Core/NodeEditor.h>

#include <ModIO.h>
#include <ImNodeFlow.h>

class Synode : public App {
public:

	Synode(const AppContext Context) : App(Context) {};

	void Render() override;
	void Process() override;
	void Shutdown() override;
	void SetupApp() override;

	ModIO::Backends::SDLNodeAudioSession * const GetSessionInterface() {
		return static_cast<ModIO::Backends::SDLNodeAudioSession * const>(m_Session->GetInterface());
	}

private:
	void InitializeAudio();
	void InitializeGraph();

	const ModIO::Transports::Signal* ProcessAudioGraph();

private:
	std::unique_ptr<ModIO::AudioSession> m_Session;
	std::unique_ptr<NodeEditor> m_NodeEditor;
	std::shared_ptr<class MasterNode> m_MasterNode;

};