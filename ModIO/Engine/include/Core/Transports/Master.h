#pragma once

#include "Core/Transports/Mixer.h"

#include <vector>
#include <memory>


namespace ModIO::Interfaces {
	class AudioSessionInterface;
};

namespace ModIO::Transports {

	class Master : public Mixer {

		friend class Interfaces::AudioSessionInterface;

	public:

		TD::SharedMixer AddMixer() {

			TD::SharedMixer mixer = std::make_shared<Mixer>();

			mMixers.emplace_back(std::move(mixer));

			return mMixers.back();
		}

	protected:
		Signal Process() override {
			
			Signal mainSignal = Signal();

			if (mChains.size() > 0) {
				Signal mainSignal = mChains[0]->Process();
			}

			for (int i = 1; i < mChains.size(); i++) {

				if (!mainSignal.mValid) {
					mainSignal = mChains[i]->Process();
					continue;
				}

				Signal signal = mChains[i]->Process();

				if (!signal.mValid) continue;

				mainSignal.CombineSignal(signal);
			}

			for (const auto& mixer : mMixers) {
				const auto& ptr = mixer.get();

				if (!mainSignal.mValid) {
					mainSignal = ptr->Process();
					continue;
				}

				Signal signal = ptr->Process();

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


		}
	private:

		std::vector<TD::SharedMixer> mMixers;

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Transports::Master, Master);
}