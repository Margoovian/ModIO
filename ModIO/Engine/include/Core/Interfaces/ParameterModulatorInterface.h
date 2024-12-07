#pragma once

#include "Core.h"

#include "Core/Interfaces/AudioGeneratorInterface.h"
#include "Core/Interfaces/AudioModifierInterface.h"

#include <functional>

namespace ModIO::Interfaces {

	// This is the interface for the parameter modulators

	class MOD_API ParameterModulatorInterface {

	public:

		virtual void Process() = 0;

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Interfaces::ParameterModulatorInterface, Modulator);
}