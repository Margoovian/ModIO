
#include <Backends/SDL3/SDLAudioSession.h>

#include <Core/Utility/Math.h>

#include <iostream>

#include <Backends/SDL3/SDLHelpers.h>
#include <Generators/SinewaveGenerator.h>
#include <Generators/SquarewaveGenerator.h>
#include <Generators/TrianglewaveGenerator.h>
#include <Generators/SawtoothGenerator.h>

namespace ModIO {

	SDLAudioSession::SDLAudioSession() : AudioSessionInterface()
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

	SDLAudioSession::~SDLAudioSession()
	{
		SDL_CloseAudioDevice(mDeviceID);
	}

	void SDLAudioSession::Initialize()
	{

		SDLCall(SDL_Init(SDL_INIT_AUDIO), "SDL Audio Initialized");

		SDLCallIsNull(mDeviceID, SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &mAudioSpecOut), "SDL Open Device");

		SDLCallIsNull(mAudioStream, SDL_CreateAudioStream(&mAudioSpecIn, &mAudioSpecOut), "SDL Create Audio Stream");

		SDLCall(SDL_BindAudioStream(mDeviceID, mAudioStream), "SDL Bind Audio Stream");

	}

	// Thread
	void SDLAudioSession::AudioLoop()
	{

		using namespace Transports;

		SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(mAudioStream));

		std::cout << "> Audio Thread\n>\t- Running\n";

		while (mPlaying) {
			int queuedData = SDL_GetAudioStreamAvailable(mAudioStream);
			if (queuedData <= (int)mTargetBufferLength) {
				
				Signal signal = ProcessMaster();

				if (signal.mValid) {
					SendBuffer(&signal);
				}
			}
			
		}

		SDL_ClearAudioStream(mAudioStream);

		std::cout << "> Audio Thread\n>\t- Terminated\n";

	}

	void SDLAudioSession::SendBuffer(Transports::Signal* signal)
	{
		SDL_PutAudioStreamData(mAudioStream, signal->mBuffer, signal->mBufferLength);
		SDL_FlushAudioStream(mAudioStream);
	}



}