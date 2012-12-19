#pragma once

#include <string>
#include <GL3/gl3.h> // Must be included before other GL headers
#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {

class SymbolLoader
{
	public:
	template<typename T>
	void loadSymbol(T & Pointer, std::string const & Symbol)
	{
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB((GLubyte const *) Symbol.c_str()));
	}

	template<typename T>
	void loadSymbolGL(T & Pointer, std::string const & Symbol)
	{
		Pointer = reinterpret_cast<T>(glXGetProcAddressARB((GLubyte const *) Symbol.c_str()));
	}
};

}
}
