#pragma once

#include "Core.h"

#define MODIO_SETUP_TYPEDEFS(type, shortName) MOD_API typedef std::unique_ptr<type> Unique##shortName;\
MOD_API typedef std::shared_ptr<type> Shared##shortName;\
MOD_API typedef std::weak_ptr<type> shortName##Ref