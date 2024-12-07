#pragma once

#include "Core.h"

#include <memory>
#include <atomic>

#include "Core/Transports/Signal.h"

namespace ModIO::Interfaces {

	// This is the interface for the audio generators

	template<typename T>
	concept AudioGenerator = requires(T t) {
		{ t.Generate() } -> Transports::AudioSignal;
	};

	class AudioGeneratorInterface {

	public:

		MOD_API virtual Transports::Signal Generate() = 0;

		MOD_API Transports::Signal CreateSignal() {
			
			return Transports::Signal(
				new float[mSampleCount],
				mSampleRate,
				mSampleCount,
				mSampleSize,
				mSampleSize * mSampleCount);

		}


		uint32_t mSampleSize = sizeof(float);
		uint32_t mSampleRate = 48000;
		uint32_t mSampleCount = 1024;

		std::atomic<float> mAmplitude = 0.05f;		// Volume: 0.0f - 1.0f
		std::atomic<float> mFrequency = 261.63f;	// Frequency in Hz
		std::atomic<double> mPhase = 0.00;			// Phase in radians

	protected:
		float mPhi = 0; // Current phase of Ocillator

	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Interfaces::AudioGeneratorInterface, Generator);
}