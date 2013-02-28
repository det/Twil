#include "Glx.hpp"

#include "SymbolLoader.hpp"

#include <stdexcept>

namespace {

struct GlxProcsT {
	decltype(&glXCreateContextAttribsARB) CreateContextAttribsARB;
};

GlxProcsT gGlxProcs;

}

namespace Twil {
namespace Platform {
namespace Glx {

void initialize(SymbolLoaderT const & Loader)
{
	Loader.loadGlArbSymbol(gGlxProcs.CreateContextAttribsARB, "glXCreateContextAttribsARB");
}

}
}
}

namespace Twil {
namespace Platform {
namespace Procs {

GLXContext glXCreateContextAttribsARB(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list)
{
	return gGlxProcs.CreateContextAttribsARB(dpy, config, share_context, direct, attrib_list);
}

}
}
}
