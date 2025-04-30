#pragma once

#include "Core.h"

#include "Core/Interfaces/AudioSessionInterface.h"

#include "SDL3/SDL.h"

#include "Core/Transports/Signal.h"

#include <functional>

namespace ModIO::Backends {

	class SDLNodeAudioSession : public Interfaces::AudioSessionInterface {

	public:

		SDLNodeAudioSession();

		~SDLNodeAudioSession();

		void Initialize() override;
		void AudioLoop() override;
		void SendBuffer(const Transports::Signal* signal) override;

		inline MOD_API void SetGraphEvaluationFunction(std::function<const ModIO::Transports::Signal*(void)>&& GraphEvaluation)
		{
			m_EvaluateCallback = GraphEvaluation;
		}

	private:
		SDL_AudioStream* mAudioStream;
		SDL_AudioDeviceID mDeviceID;
		SDL_AudioSpec mAudioSpecIn;
		SDL_AudioSpec mAudioSpecOut;
		uint32_t mTargetBufferLength = 4096;

		std::function<const ModIO::Transports::Signal*(void)> m_EvaluateCallback;

	};

}