#pragma once

#include "Core.h"
#include "Core/Interfaces/AudioModifierInterface.h"
#include "Core/Transports/Signal.h"

namespace ModIO::Modifiers {

	class MOD_API Lowpass : public Interfaces::AudioModifierInterface {

	public:

		void Process(Transports::Signal&& signal) override;

		float mCutoff = 200.00f;

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Modifiers::Lowpass, Lowpass);
}