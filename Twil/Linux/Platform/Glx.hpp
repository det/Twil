#pragma once

#include "GlxFwd.hpp"

#include "SymbolLoaderFwd.hpp"

#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {
namespace Procs {

GLXContext glXCreateContextAttribsARB(Display *, GLXFBConfig, GLXContext, Bool, const int *);

}
}
}

using namespace Twil::Platform::Procs;

namespace Twil {
namespace Platform {

namespace Glx {

/// \brief Load all glX symbols.
void initialize(SymbolLoaderT const &);

}

}
}
