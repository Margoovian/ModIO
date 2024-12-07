#pragma once

#include "Core.h"

#include "AudioSession.h"

#include "Includes.h"

#include <memory>

namespace ModIO {

	 static std::unique_ptr<ModIO::AudioSession> CreateSession() {
	 	return std::unique_ptr<AudioSession>(new AudioSession());
	 }

	 template<typename T>
	 static std::shared_ptr<T> GetShared(std::weak_ptr<T> ref) {
		 if (ref.expired())
			 return nullptr;
		 return ref.lock();
	 }

}