#include <Generators/TrianglewaveGenerator.h>

#include <Core/Utility/Math.h>

namespace ModIO::Generators {

	Transports::Signal TrianglewaveGenerator::Generate()
	{
		Transports::Signal signal = CreateSignal();

		for (int t = 0; t < (int)signal.mSampleCount; t++) {					
			float sample = Trianglewave();
			signal.mBuffer[t] = sample;
		}	
		

		return signal;
	}

	float TrianglewaveGenerator::Trianglewave()
	{
		float sine = (float)sin(mPhi + mPhase);
		float triangle = (float)asin(sine);

		float result = (float)(2 * mAmplitude / PI) * triangle;

		float delta = (float)(1.0f / (float)mSampleRate);

		mPhi += (float)(Two_PI * mFrequency * delta);
		mPhi += (float)((mPhi >= Two_PI) * -Two_PI) + (float)((mPhi < 0.0) * Two_PI);

		return  result;
	}

}