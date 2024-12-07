#include <Modifiers/Lowpass.h>

#include "Core/Utility/Math.h"

namespace ModIO::Modifiers {

	void Lowpass::Process(Transports::Signal&& signal)
	{

		float* y = new float[signal.mSampleCount];

		float prevFreq = 0;

		for (int i = 0; i < (int)signal.mSampleCount; i++) {
			float freq = signal.mBuffer[i];

			float freqTan = (float)tan(PI * mCutoff / signal.mSampleRate);

			float  a1 = (float)(freqTan - 1) / (float)(freqTan + 1);

			y[i] = a1 * signal.mBuffer[i] + prevFreq;

			prevFreq = signal.mBuffer[i] - a1 * y[i];

		}

		for (int i = 0; i < (int)signal.mSampleCount; i++) {
			y[i] *= 1;
			signal.mBuffer[i] += y[i];
		}

		delete[] y;

	}

}