#include "SymbolLoader.hpp"

namespace Twil {
namespace Platform {

SymbolLoaderT::SymbolLoaderT()
{
	mHandle = dlopen("libGL.so.1", RTLD_LAZY | RTLD_GLOBAL);
	if (mHandle == nullptr) throw std::runtime_error{"Unable to open the OpenGL library"};
}

SymbolLoaderT::~SymbolLoaderT()
{
	dlclose(mHandle);
}

}
}
