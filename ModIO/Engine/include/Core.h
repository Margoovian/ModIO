#pragma once

#include <cstdint>

#ifdef MOD_BUILD_DLL 

 #ifdef MOD_PLATFORM_WINDOWS
  #define MOD_API __declspec(dllexport)

   #ifdef MOD_BACKEND_NODE
    constexpr uint8_t MODIO_PLATFORM = 1;
   #else
    constexpr uint8_t MODIO_PLATFORM = 0;
   #endif

 #else
  #error ModIO only supports windows!
 #endif

#else

 #ifdef MOD_PLATFORM_WINDOWS
  #define MOD_API __declspec(dllimport)

   #ifdef MOD_BACKEND_NODE
    constexpr uint8_t MODIO_PLATFORM = 1;
   #else
    constexpr uint8_t MODIO_PLATFORM = 0;
   #endif

 #else
  #error ModIO only supports windows!
 #endif

#endif 