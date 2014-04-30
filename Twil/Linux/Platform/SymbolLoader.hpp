#pragma once

#include "SymbolLoaderFwd.hpp"

namespace Twil {
namespace Platform {

/// \brief Loads OpenGL function pointers.
class SymbolLoaderT
{
private:
	using FunctionPointerT = void (*) ();
	static FunctionPointerT loadArb(char const *);

public:
	// These are the same on Linux

	/// \brief Load an OpenGL 1.1 function pointer.
	template<typename T>
	static void loadGlSymbol(T & Pointer, char const * Symbol)
	{
		Pointer = reinterpret_cast<T>(loadArb(Symbol));
	}

	/// \brief Load an OpenGL 1.1+ function pointer.
	template<typename T>
	static void loadGlArbSymbol(T & Pointer, char const * Symbol)
	{
		Pointer = reinterpret_cast<T>(loadArb(Symbol));
	}
};

}
}
