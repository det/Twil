#pragma once

#include <string>
#include <GL3/gl3.h> // Must be included before other GL headers
#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {

class SymbolLoader {
	public:
	template<typename T>
	void loadSymbol(T &, std::string const &);
	template<typename T>
	void loadSymbolGL(T &, std::string const &);
};

template<typename T>
void SymbolLoader::loadSymbol(T & pointer, std::string const & symbol)
{
	pointer = reinterpret_cast<T>(glXGetProcAddressARB((GLubyte const *) symbol.c_str()));
}

template<typename T>
void SymbolLoader::loadSymbolGL(T & pointer, std::string const & symbol)
{
	pointer = reinterpret_cast<T>(glXGetProcAddressARB((GLubyte const *) symbol.c_str()));
}

}
}
