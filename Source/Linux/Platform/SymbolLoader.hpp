#pragma once

#include "Glx.hpp"

#include <stdexcept>
#include <string>

#include <dlfcn.h>

namespace Twil {
namespace Platform {

/// \brief Loads OpenGL function pointers.
class SymbolLoaderT
{
	private:
	void * mHandle;

	public:
	SymbolLoaderT();
	~SymbolLoaderT();

	/// \brief Load a glX pointer.
	template<typename T>
	void loadGlxSymbol(T & Pointer, char const * Symbol) const
	{
		// Casting void * to a function pointer is undefined behaviour
		// This is the work around, see the manpage for dlsym(3)
		*reinterpret_cast<void * *>(&Pointer) = dlsym(mHandle, Symbol);
	}

	/// \brief Load a glX ARB symbol.
	template<typename T>
	static void loadGlxArbSymbol(T & Pointer, char const * Symbol)
	{
		auto String = reinterpret_cast<GLubyte const *>(Symbol);
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB(String));
	}

	// These are the same on Linux

	/// \brief Load an OpenGL 1.1 function pointer.
	template<typename T>
	void loadGlSymbol(T & Pointer, char const * Symbol) const
	{
		auto String = reinterpret_cast<GLubyte const *>(Symbol);
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB(String));
	}

	/// \brief Load an OpenGL 1.1+ function pointer.
	template<typename T>
	void loadGlArbSymbol(T & Pointer, char const * Symbol) const
	{
		auto String = reinterpret_cast<GLubyte const *>(Symbol);
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB(String));
	}
};

}
}
