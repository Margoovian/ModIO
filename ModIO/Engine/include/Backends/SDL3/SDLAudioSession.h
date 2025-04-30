#pragma once

#include "Core.h"

#include "Core/Interfaces/AudioSessionInterface.h"

#include "SDL3/SDL.h"

namespace ModIO::Backends {

	class SDLAudioSession : public Interfaces::AudioSessionInterface {
		
	public:

		SDLAudioSession();

		~SDLAudioSession();

		void Initialize() override;			
		void AudioLoop() override;		
		void SendBuffer(const Transports::Signal* signal) override;
	private:
		SDL_AudioStream* mAudioStream;
		SDL_AudioDeviceID mDeviceID;
		SDL_AudioSpec mAudioSpecIn;
		SDL_AudioSpec mAudioSpecOut;
		uint32_t mTargetBufferLength = 4096;

	};

}