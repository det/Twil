#include "symbol_loader.hpp"

#include "glx.hpp"

#include <cstdint>

namespace twil {
namespace platform {

SymbolLoader::FunctionPointer SymbolLoader::LoadArb(char const * symbol)
{
	auto String = reinterpret_cast<std::uint8_t const *>(symbol);
	return glXGetProcAddressARB(String);
}

}
}
