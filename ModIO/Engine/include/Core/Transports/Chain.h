#pragma once

#include "Core.h"

#include "Core/Transports/Signal.h"
#include "Core/Interfaces/AudioComponentInterface.h"
#include "Core/Interfaces/AudioGeneratorInterface.h"
#include "Core/Interfaces/ParameterModulatorInterface.h"
#include "Core/Interfaces/AudioTransportInterface.h"

#include <vector>
#include <memory>

namespace ModIO::Transports {

	class Chain : public Interfaces::AudioTransportInterface {

		friend class Mixer;
		friend class Master;

	public:
		template<Interfaces::AudioGenerator Generator>
		TD::GeneratorRef SetGenerator() {
			if (!mGenerator) {
				mGenerator = std::make_shared<Generator>();
				mReady = true;
				return mGenerator;
			}

			mGenerator = std::make_shared<Generator>();
		
			mReady = true; // Not needed in theory
			return mGenerator;
		};

	protected:

		Signal Process() override {

			if (!mReady) {
				return Signal();
			}

			Signal signal = mGenerator->Generate();

			for (const auto& component : mComponents) {
				const auto& ptr = component.get();
#pragma warning( push )
#pragma warning( disable : 26800)
				ptr->Process(std::move(signal)); // CS26800 bug in VS studio
#pragma warning( pop )
			}

			return signal;

		};

	private:

		TD::SharedGenerator mGenerator = 0;
		bool mReady = false;

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Transports::Chain, Chain);
}