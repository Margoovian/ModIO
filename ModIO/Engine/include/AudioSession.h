#pragma once

#include "Core/Interfaces/AudioSessionInterface.h"

#include <thread>

namespace ModIO {

	// This is a wrapper of the AudioSessionInterface class for the end user

	class AudioSession {
		
	public:

		MOD_API AudioSession();

		MOD_API ~AudioSession();

		MOD_API void Start();
		MOD_API void Stop();
		MOD_API bool IsRunning();
		MOD_API ModIO::Interfaces::AudioSessionInterface * const GetInterface();

		MOD_API TD::WeakMaster GetMaster();
 
	private:

		void RunAudioThread();
		void StopAudioThread();

		Interfaces::AudioSessionInterface* mAudioSessionInterface;

	};

}