#pragma once

#include <string>
#include <GL3/gl3.h> // Must be included before other GL headers
#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {

/// \brief Loads OpenGL function pointers.
class SymbolLoaderT
{
	public:
	// These are the same on Linux

	/// \brief Load an OpenGL 1.1 function pointer.
	template<typename T>
	void loadSymbolGL(T & Pointer, char const * Symbol) const
	{
		auto String = reinterpret_cast<GLubyte const *>(Symbol);
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB(String));
	}

	/// \brief Load an OpenGL 1.1+ function pointer.
	template<typename T>
	void loadSymbol(T & Pointer, char const * Symbol) const
	{
		auto String = reinterpret_cast<GLubyte const *>(Symbol);
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB(String));
	}
};

}
}
