#include "Glx.hpp"

#include "SymbolLoader.hpp"

#include <stdexcept>

namespace {

decltype(&glXCreateContextAttribsARB) gCreateContextAttribsARB;

}

namespace Twil {
namespace Platform {
namespace Glx {

void initialize(SymbolLoaderT const & Loader)
{
	Loader.loadGlArbSymbol(gCreateContextAttribsARB, "glXCreateContextAttribsARB");
}

}
}
}

namespace Twil {
namespace Platform {
namespace Procs {

GLXContext glXCreateContextAttribsARB(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list)
{
	return gCreateContextAttribsARB(dpy, config, share_context, direct, attrib_list);
}

}
}
}
