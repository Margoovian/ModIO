#pragma once
#include <cstdint>
#include <cassert>
#include <concepts>

namespace ModIO::Transports {

	template<typename T>
	concept AudioSignal = requires(T t) {
		{ t.mBuffer };
	};

	class Signal {
	public:

		Signal(
			float* buffer,
			uint32_t sampleRate,
			uint32_t sampleCount,
			uint32_t sampleSize,
			uint32_t bufferLength
		) {
			mBuffer = buffer;
			mSampleRate = sampleRate;
			mSampleCount = sampleCount;
			mSampleSize = sampleSize;
			mBufferLength = bufferLength;
			mValid = true;
		}

		Signal() : 
			mBuffer(nullptr),
			mBufferLength(0),
			mSampleRate(0),
			mSampleCount(0),
			mSampleSize(0),
			mValid(false) { }

		~Signal() {
			if(mValid)
				delete[] mBuffer;
		}

		Signal(const Signal& other) = delete;
		Signal& operator=(const Signal& other) = delete;

		Signal(Signal&& other) noexcept
		{
			Move(std::move(other));
		}

		Signal& operator=(Signal&& other) noexcept {
			if (this != &other) {
				delete[] mBuffer;

				Move(std::move(other));

			}

			return *this;

		}

		template<AudioSignal... Signals>
		void CombineSignals(Signals&&... signals) {
			([&] {

				for (int i = 0; i < (int)mSampleCount; i++) {
					mBuffer[i] += signals.mBuffer[i];
				}

				}(), ...);
		}

		void CombineSignal(const Signal& signal) {
			
			for (int i = 0; i < (int)mSampleCount; i++) {
				mBuffer[i] += signal.mBuffer[i];
			}

		}

		Signal operator+(Signal const& signal) {

			Signal newSignal;

			newSignal.mBufferLength = mBufferLength;
			newSignal.mSampleRate	= mSampleRate;
			newSignal.mSampleCount	= mSampleCount;
			newSignal.mSampleSize	= mSampleSize;

			float* newBuffer = new float[mSampleCount];

			if (signal.mSampleCount < mSampleCount )
				assert("Buffer is smaller then new buffer");

			for (int i = 0; i < (int)mSampleCount; i++) {
				newBuffer[i] = signal.mBuffer[i] + mBuffer[i];
			}

			newSignal.mBuffer = newBuffer;

			return newSignal;

		}

		float* mBuffer;			// Sample Data
		uint32_t mBufferLength; // Size of buffer in bytes
		uint32_t mSampleRate;	// Rate the data is sampled
		uint32_t mSampleCount; // The amount of samples
		uint32_t mSampleSize;	// Size of each sample in bytes

		bool mValid = false;


		private:

			void Move(Signal&& other) {
				mBuffer = other.mBuffer;
				mBufferLength = other.mBufferLength;
				mSampleCount = other.mSampleCount;
				mSampleRate = other.mSampleRate;
				mSampleSize = other.mSampleSize;
				mValid = other.mValid;

				other.mBuffer = nullptr;
			}

	};

}