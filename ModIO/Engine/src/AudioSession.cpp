
#include "AudioSession.h"

#include <Backends/SDL3/SDLAudioSession.h>
#include <cassert>
#include <functional>

namespace ModIO {


	AudioSession::AudioSession()
	{

		if (MODIO_PLATFORM == 0)
			mAudioSessionInterface = new SDLAudioSession();
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

	void AudioSession::RunAudioThread()
	{
		mAudioSessionInterface->mPlaying = true;
		std::thread(std::bind(&Interfaces::AudioSessionInterface::AudioLoop, mAudioSessionInterface)).detach();
	}

	void AudioSession::StopAudioThread()
	{
		mAudioSessionInterface->mPlaying = false;
	}

	TD::MasterRef AudioSession::GetMaster() {
		return mAudioSessionInterface->mMaster;
	}
}