#pragma once

#include <cstdint>

#ifdef MOD_BUILD_DLL 

 #ifdef MOD_PLATFORM_WINDOWS
  #define MOD_API __declspec(dllexport)
  constexpr uint8_t MODIO_PLATFORM = 0; 

 #else
  #error ModIO only supports windows!
 #endif

#else

 #ifdef MOD_PLATFORM_WINDOWS
  #define MOD_API __declspec(dllimport)
  constexpr uint8_t MODIO_PLATFORM = 0;

 #else
  #error ModIO only supports windows!
 #endif

#endif 