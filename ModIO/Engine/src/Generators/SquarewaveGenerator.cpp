#include <Generators/SquarewaveGenerator.h>

#include <Core/Utility/Math.h>

namespace ModIO::Generators {

	Transports::Signal SquarewaveGenerator::Generate()
	{
		Transports::Signal signal = CreateSignal();

		for (int t = 0; t < (int)signal.mSampleCount; t++) {
			float sample = Squarewave();
			signal.mBuffer[t] = sample;
		}

		return signal;
	}

	float SquarewaveGenerator::Squarewave()
	{

		float sine = (float)sin(mPhi + mPhase);
		float square = (float)(sine > 0) - (float)(sine < 0);

		float result = (float)(mAmplitude * square);

		float delta = (float)(1.0f / (float)mSampleRate);

		mPhi += (float)(Two_PI * mFrequency * delta);
		mPhi += (float)((mPhi >= Two_PI) * -Two_PI) + (float)((mPhi < 0.0) * Two_PI);

		return  result;
	}

}