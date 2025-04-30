#include "AudioSession.h"

#include "AudioSession.h"

#include <Backends/SDL3/SDLAudioSession.h>
#include <Backends/SDL3/SDLNodeAudioSession.h>
#include <cassert>
#include <functional>

namespace ModIO {


	AudioSession::AudioSession()
	{

		if (MODIO_PLATFORM == 0)
			mAudioSessionInterface = new Backends::SDLAudioSession();
		else if(MODIO_PLATFORM == 1)
			mAudioSessionInterface = new Backends::SDLNodeAudioSession();
		else
			assert(false);


		mAudioSessionInterface->Initialize();

	}

	AudioSession::~AudioSession()
	{
		Stop();
		delete mAudioSessionInterface;
	}

	void AudioSession::Start()
	{
		RunAudioThread();
	}

	void AudioSession::Stop()
	{
		StopAudioThread();
	}

	bool AudioSession::IsRunning()
	{
		if (!mAudioSessionInterface) return false;
		return mAudioSessionInterface->mPlaying;
	}

	ModIO::Interfaces::AudioSessionInterface* const  AudioSession::GetInterface()
	{
		return mAudioSessionInterface;
	}

	void AudioSession::RunAudioThread()
	{
		mAudioSessionInterface->mPlaying = true;
		std::thread(std::bind(&Interfaces::AudioSessionInterface::AudioLoop, mAudioSessionInterface)).detach();
	}

	void AudioSession::StopAudioThread()
	{
		mAudioSessionInterface->mPlaying = false;
	}

	TD::WeakMaster AudioSession::GetMaster() {
		return mAudioSessionInterface->mMaster;
	}
}