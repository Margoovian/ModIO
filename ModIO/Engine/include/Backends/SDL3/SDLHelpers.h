#pragma once

#include <iostream>
#include "SDL3/SDL.h"
#include <string>

#define SDLUSERASSERT(x) if (!(x)) __debugbreak();
#define SDLCall(x,s) SDL_ClearError();\
	SDLUSERASSERT(ModIO::SDLLogCall(x,#x,__FILE__, __LINE__,s))

#define SDLCallIsNull(x,f,s) SDL_ClearError();\
	x = f;\
	SDLUSERASSERT(ModIO::SDLLogCall(ModIO::SDLCheckNull(x),#x,__FILE__, __LINE__,s))



namespace ModIO {

	template<typename T>
	static int SDLCheckNull(T& result) {
		if (result == NULL) return -1; else return 0;
	}

	static bool SDLLogCall(int result, const char* function,const char* file, int line, const char* displayName = "Unnamed Command") {

		std::string error = SDL_GetError();

		if (error == "" || result >= 0) {

			std::cout << "> " << displayName << "\n"
				<< ">   " << "- OK" << "\n";

			return true;
		}

		std::cout << "> " << displayName << "\n"
			 << ">   "<< "- Fail" << "\n"
			 << ">     "<< "+ Error: " << error <<"\n"
			 << ">     "<< "+ File: " << file << "\n"
			 << ">     "<< "+ Line: " << line << "\n";

		return false;

	}

}