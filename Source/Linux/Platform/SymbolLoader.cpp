#include "SymbolLoader.hpp"

#include "Glx.hpp"

namespace Twil {
namespace Platform {

SymbolLoaderT::FunctionPointerT SymbolLoaderT::loadArb(char const * Symbol)
{
	auto String = reinterpret_cast<GLubyte const *>(Symbol);
	return glXGetProcAddressARB(String);
}

}
}
