#pragma once

#include "Core/Transports/Signal.h"

#include <memory>


namespace ModIO::Interfaces {

	template<typename T>
	concept AudioComponent = requires(T t) {
		{ t.Process(Transports::Signal()) };
	};


	class MOD_API AudioComponentInterface {
	public:
		virtual void Process(Transports::Signal&& signal) = 0;
	};

}

#include "Core/Utility/Defines.h"

namespace ModIO::TD {
	MODIO_SETUP_TYPEDEFS(Interfaces::AudioComponentInterface, Component);
}