
#include <Backends/SDL3/SDLNodeAudioSession.h>

#include <Core/Utility/Math.h>

#include <iostream>

#include <Backends/SDL3/SDLHelpers.h>
#include <Generators/SinewaveGenerator.h>
#include <Generators/SquarewaveGenerator.h>
#include <Generators/TrianglewaveGenerator.h>
#include <Generators/SawtoothGenerator.h>

namespace ModIO::Backends {

	SDLNodeAudioSession::SDLNodeAudioSession() : AudioSessionInterface()
	{
		mAudioSpecOut = SDL_AudioSpec{
			SDL_AUDIO_F32,
			2,
			48000
		};

		mAudioSpecIn = SDL_AudioSpec{
			SDL_AUDIO_F32,
			1,
			48000
		};

		mAudioStream = 0;
		mDeviceID = 0;

	}

	SDLNodeAudioSession::~SDLNodeAudioSession()
	{
		SDL_CloseAudioDevice(mDeviceID);
	}

	void SDLNodeAudioSession::Initialize()
	{

		SDLCall(SDL_Init(SDL_INIT_AUDIO), "SDL Audio Initialized");

		SDLCallIsNull(mDeviceID, SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &mAudioSpecOut), "SDL Open Device");

		SDLCallIsNull(mAudioStream, SDL_CreateAudioStream(&mAudioSpecIn, &mAudioSpecOut), "SDL Create Audio Stream");

		SDLCall(SDL_BindAudioStream(mDeviceID, mAudioStream), "SDL Bind Audio Stream");

	}

	// Thread
	void SDLNodeAudioSession::AudioLoop()
	{

		using namespace Transports;

		SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(mAudioStream));

		std::cout << "> Audio Thread\n>\t- Running\n";

		while (mPlaying) {
			int queuedData = SDL_GetAudioStreamAvailable(mAudioStream);
			if (queuedData <= (int)mTargetBufferLength) {
				
				const Signal* signal = m_EvaluateCallback();

				if (signal->mValid) {
					SendBuffer(signal);
				}
			}
			
		}

		SDL_ClearAudioStream(mAudioStream);

		std::cout << "> Audio Thread\n>\t- Terminated\n";

	}

	void SDLNodeAudioSession::SendBuffer(const Transports::Signal* signal)
	{
		SDL_PutAudioStreamData(mAudioStream, signal->mBuffer, signal->mBufferLength);
		SDL_FlushAudioStream(mAudioStream);
	}



}