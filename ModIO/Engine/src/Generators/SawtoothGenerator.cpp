#include <Generators/SawtoothGenerator.h>

#include <Core/Utility/Math.h>

namespace ModIO::Generators {

	Transports::Signal SawtoothGenerator::Generate()
	{
		Transports::Signal signal = CreateSignal();

		for (int t = 0; t < (int)signal.mSampleCount; t++) {
			float sample = Sawtooth();
			signal.mBuffer[t] = sample;
		}

		return signal;
	}

	float SawtoothGenerator::Sawtooth()
	{

		float saw = (float)(2 * atan(tan((mPhi + mPhase)/2)));

		float result = 0.5f * mAmplitude * saw;

		float delta = (1.0f / (float)mSampleRate);

		mPhi += (float)(Two_PI * mFrequency * delta);
		mPhi += (float)(((mPhi >= Two_PI) * -Two_PI)) + (float)(((mPhi < 0.0) * Two_PI));

		return  result;
	}
}