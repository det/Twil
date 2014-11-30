#include "glx.hpp"

#include "symbol_loader.hpp"

#include <stdexcept>

namespace {

decltype(&glXCreateContextAttribsARB) gCreateContextAttribsARB;

}

namespace twil {
namespace platform {
namespace glx {

void Initialize(SymbolLoader const & loader)
{
	loader.loadGlArbSymbol(gCreateContextAttribsARB, "glXCreateContextAttribsARB");
}

}
}
}

namespace twil {
namespace platform {
namespace procs {

GLXContext glXCreateContextAttribsARB(Display * dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int * attrib_list)
{
	return gCreateContextAttribsARB(dpy, config, share_context, direct, attrib_list);
}

}
}
}
