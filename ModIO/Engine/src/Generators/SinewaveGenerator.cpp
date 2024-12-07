#include <Generators/SinewaveGenerator.h>

#include <Core/Utility/Math.h>

namespace ModIO::Generators {


	Transports::Signal SinewaveGenerator::Generate()
	{
		Transports::Signal signal = CreateSignal();

		for (int t = 0; t < (int)signal.mSampleCount; t++) {
			float sample = Sinewave();
			signal.mBuffer[t] = sample;
		}

		return signal;
	}

	float SinewaveGenerator::Sinewave()
	{

		float result = (float)(mAmplitude * sin(mPhi + mPhase));

		float delta = (float)(1.0f / (float)mSampleRate);

		mPhi += (float)(Two_PI * mFrequency * delta);
		mPhi += (float)(((mPhi >= Two_PI) * -Two_PI) + ((mPhi < 0.0) * Two_PI));

		return  result;
	}

}