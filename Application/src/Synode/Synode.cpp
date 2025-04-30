#include "Synode.h"

void Synode::Render()
{
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

	using namespace ModIO;

	m_Session = ModIO::CreateSession();

	TD::MasterRef masterRef = m_Session->GetMaster();

	TD::SharedMaster master = GetShared(masterRef);

	if (master)
	{

		TD::SharedMixer mixer = master->AddMixer();

		TD::SharedChain chain = mixer->AddChain();

		TD::GeneratorRef generatorA = chain->SetGenerator<Generators::SawtoothGenerator>();
		TD::GeneratorRef generatorB = mixer->AddChain()->SetGenerator<Generators::SawtoothGenerator>();
		TD::GeneratorRef generatorC = mixer->AddChain()->SetGenerator<Generators::SawtoothGenerator>();
		TD::GeneratorRef generatorD = mixer->AddChain()->SetGenerator<Generators::SawtoothGenerator>();

		GetShared(generatorA)->mFrequency = 261.63f;
		GetShared(generatorB)->mFrequency = 329.63f;
		GetShared(generatorC)->mFrequency = 392.00f;
		GetShared(generatorD)->mFrequency = 32.70f;

		//TD::SharedComponent lowPass = chain->InsertComponent<Modifiers::Lowpass>();

		m_Session->Start();

	}

}
