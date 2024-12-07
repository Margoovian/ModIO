#pragma once

#include <memory>
#include <vector>

#include "Core/Interfaces/AudioComponentInterface.h"

namespace ModIO::Interfaces {

	class AudioTransportInterface {
	public:

		template<AudioComponent Component>
		TD::SharedComponent InsertComponent() {
		
			TD::SharedComponent component = std::make_shared<Component>();
		
			mComponents.emplace_back(std::move(component));
		
			return mComponents.back();
		
		}

	protected:
		virtual Transports::Signal Process() = 0;
		std::vector<TD::SharedComponent> mComponents;

	};

}