#pragma once

#include "Core.h"

#include "Core/Transports/Signal.h"
#include "Core/Interfaces/AudioComponentInterface.h"

#include <vector>
#include <memory>
#include <functional>

namespace ModIO::Interfaces {

	// This is the interface for the audio Modifiers (effects)

	class MOD_API AudioModifierInterface : public AudioComponentInterface {

	public:

		virtual void Process(Transports::Signal&& signal) = 0;

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Interfaces::AudioModifierInterface, Modifier);
}