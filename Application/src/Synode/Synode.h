#pragma once

#include <Core/App.h>
#include <ModIO.h>

class Synode : public App {
public:

	Synode(const AppContext Context) : App(Context) {};

	void Render() override;
	void Process() override;
	void Shutdown() override;
	void SetupApp() override;

private:
	std::unique_ptr<ModIO::AudioSession> m_Session;

};