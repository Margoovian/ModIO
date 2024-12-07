#pragma once

#include "Core.h"

#include "Core/Transports/Master.h"
#include "Core/Transports/Signal.h"

#include <array>
#include <atomic>

namespace ModIO::Interfaces {

	// This is the interface for the audio session ( for later crossplatform support )

	class AudioSessionInterface {

	public:
		AudioSessionInterface() {};
		virtual ~AudioSessionInterface() = default;

		virtual void Initialize() = 0;

		// Thread safe functions
		virtual void AudioLoop() = 0;

		virtual void SendBuffer(Transports::Signal* signal) = 0;

		Transports::Signal ProcessMaster() {
			return mMaster->Process();
		}

		TD::SharedMaster mMaster = std::make_shared<Transports::Master>();
		std::atomic_bool mPlaying;
	};
}