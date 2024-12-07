#pragma once

#include "Core.h"

#include "Core/Interfaces/AudioGeneratorInterface.h"

namespace ModIO::Generators {

	using namespace Interfaces;
	using namespace Transports;

	class SinewaveGenerator : public Interfaces::AudioGeneratorInterface {
	public:

		MOD_API Signal Generate() override;

	private:
		float Sinewave();
		
	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Generators::SinewaveGenerator, SinewaveGenerator);
}