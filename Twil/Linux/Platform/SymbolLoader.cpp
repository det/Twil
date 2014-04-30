#include "SymbolLoader.hpp"

#include "Glx.hpp"

#include <cstdint>

namespace Twil {
namespace Platform {

SymbolLoaderT::FunctionPointerT SymbolLoaderT::loadArb(char const * Symbol)
{
	auto String = reinterpret_cast<std::uint8_t const *>(Symbol);
	return glXGetProcAddressARB(String);
}

}
}
