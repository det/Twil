#pragma once

#include "Gl/Context.hpp"

#include <GL/glx.h>
#include <GL/glxext.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

extern "C" {

using __GLXextFuncPtr = void (*)();
using GLXFBConfig = struct __GLXFBConfigRec *;
using GLXContext = struct __GLXcontextRec *;
using GLXDrawable = XID;

__GLXextFuncPtr glXGetProcAddressARB(const GLubyte *);
GLXFBConfig * glXChooseFBConfig(Display *, int, const int *, int *);
XVisualInfo * glXGetVisualFromFBConfig(Display *, GLXFBConfig);
Bool glXMakeCurrent(Display *, GLXDrawable, GLXContext);
void glXSwapBuffers(Display *, GLXDrawable);
GLXContext glXCreateContextAttribsARB(Display *, GLXFBConfig, GLXContext, Bool, const int *);
void glXDestroyContext(Display *, GLXContext);

}

namespace Twil {
namespace Platform {

class SymbolLoaderT;

namespace Glx {

/// \brief Load all glX symbols.
void initialize(SymbolLoaderT const &);

}

}
}
