#pragma once

#include "Core.h"

#define MODIO_SETUP_TYPEDEFS(type, shortName) MOD_API typedef std::unique_ptr<type> Unique##shortName;\
MOD_API typedef std::shared_ptr<type> Shared##shortName;\
MOD_API typedef std::weak_ptr<type> Weak##shortName;\
MOD_API typedef std::reference_wrapper<type> shortName##Ref;\
MOD_API typedef std::reference_wrapper<const type> shortName##CRef;