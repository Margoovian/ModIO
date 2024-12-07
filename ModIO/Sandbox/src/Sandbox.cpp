
#include <ModIO.h>

#include <iostream>
#include <memory>

int main(int argc, wchar_t* argv[]) {

	using namespace ModIO;

	std::unique_ptr<AudioSession> session = ModIO::CreateSession();

	TD::MasterRef masterRef = session->GetMaster();

	TD::SharedMaster master = GetShared(masterRef);

	if (master) {

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
	}

	session->Start();

	while (session->IsRunning()) {

	};

}