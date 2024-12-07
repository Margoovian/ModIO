#pragma once

#include "Core.h"

#include "Core/Interfaces/AudioGeneratorInterface.h"

namespace ModIO::Generators {

	class SawtoothGenerator : public Interfaces::AudioGeneratorInterface {

	public:

		MOD_API Transports::Signal Generate() override;

	private:
		float Sawtooth();


	};

}


#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Generators::SawtoothGenerator, SawtoothGenerator);
}