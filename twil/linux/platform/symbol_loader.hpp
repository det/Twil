#pragma once

#include "symbol_loader.hxx"

namespace twil {
namespace platform {

/// \brief Loads OpenGL function pointers.
class SymbolLoader
{
private:
	using FunctionPointer = void (*) ();
	static FunctionPointer LoadArb(char const *);

public:
	// These are the same on Linux

	/// \brief Load an OpenGL 1.1 function pointer.
	template<typename T>
	static void loadGlSymbol(T & pointer, char const * symbol)
	{
		pointer = reinterpret_cast<T>(LoadArb(symbol));
	}

	/// \brief Load an OpenGL 1.1+ function pointer.
	template<typename T>
	static void loadGlArbSymbol(T & pointer, char const * symbol)
	{
		pointer = reinterpret_cast<T>(LoadArb(symbol));
	}
};

}
}
