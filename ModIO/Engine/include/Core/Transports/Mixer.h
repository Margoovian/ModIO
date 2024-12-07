#pragma once

#include "Core.h"

#include "Core/Transports/Signal.h"
#include "Core/Transports/Chain.h"
#include "Core/Interfaces/AudioTransportInterface.h"

#include <vector>
#include <memory>

namespace ModIO::Interfaces {
	class AudioSessionInterface;
};

namespace ModIO::Transports {

	class  Mixer : public Interfaces::AudioTransportInterface {

		friend class Interfaces::AudioSessionInterface;
		friend class Master;

	public:

		MOD_API TD::SharedChain AddChain() {

			TD::SharedChain chain = std::make_shared<Chain>();

			mChains.emplace_back(std::move(chain));

			return mChains.back();
		}

	protected:

		virtual Signal Process() override {
		
			if (mChains.size() <= 0) {
				return Signal();
			}

			Signal mainSignal = mChains[0]->Process();

			for (int i = 1; i < mChains.size(); i++) {
				if (!mainSignal.mValid) { 
					mainSignal = mChains[i]->Process();
					continue;
				}

				Signal signal = mChains[i]->Process();

				if (!signal.mValid) continue;
				mainSignal.CombineSignal(signal);
			}

			for (const auto& component : mComponents) {
				const auto& ptr = component.get();
#pragma warning( push )
#pragma warning( disable : 26800)
				ptr->Process(std::move(mainSignal)); // CS26800 bug in VS studio
#pragma warning( pop )
			}

			return mainSignal;

		};

		std::vector<std::shared_ptr<Chain>> mChains;

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Transports::Mixer, Mixer);
}