#pragma once

#include "glx.hxx"

#include "symbol_loader.hxx"

#include <GL/glx.h>
#include <GL/glxext.h>

namespace twil {
namespace platform {
namespace procs {

GLXContext glXCreateContextAttribsARB(Display *, GLXFBConfig, GLXContext, Bool, const int *);

}
}
}

using namespace twil::platform::procs;

namespace twil {
namespace platform {

namespace glx {

/// \brief Load all glX symbols.
void Initialize(SymbolLoader const &);

}

}
}
