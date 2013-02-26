#include "Glx.hpp"

#include "SymbolLoader.hpp"

#include <stdexcept>

namespace {

struct GlxProcsT {
	decltype(&glXGetProcAddressARB) GetProcAddressARB;
	decltype(&glXChooseFBConfig) ChooseFBConfig;
	decltype(&glXGetVisualFromFBConfig) GetVisualFromFBConfig;
	decltype(&glXMakeCurrent) MakeCurrent;
	decltype(&glXSwapBuffers) SwapBuffers;
	decltype(&glXCreateContextAttribsARB) CreateContextAttribsARB;
	decltype(&glXDestroyContext) DestroyContext;
};

GlxProcsT gGlxProcs;

}

namespace Twil {
namespace Platform {
namespace Glx {

void initialize(SymbolLoaderT const & Loader)
{
	Loader.loadGlxSymbol(gGlxProcs.GetProcAddressARB, "glXGetProcAddressARB");
	Loader.loadGlxSymbol(gGlxProcs.ChooseFBConfig, "glXChooseFBConfig");
	Loader.loadGlxSymbol(gGlxProcs.GetVisualFromFBConfig, "glXGetVisualFromFBConfig");
	Loader.loadGlxSymbol(gGlxProcs.MakeCurrent, "glXMakeCurrent");
	Loader.loadGlxSymbol(gGlxProcs.SwapBuffers, "glXSwapBuffers");
	Loader.loadGlxSymbol(gGlxProcs.DestroyContext, "glXDestroyContext");
	Loader.loadGlxArbSymbol(gGlxProcs.CreateContextAttribsARB, "glXCreateContextAttribsARB");
}

}
}
}

extern "C" {

__GLXextFuncPtr glXGetProcAddressARB(const GLubyte * procname)
{
	return gGlxProcs.GetProcAddressARB(procname);
}

GLXFBConfig * glXChooseFBConfig(Display *dpy, int screen, const int *attrib_list, int *nelements)
{
	return gGlxProcs.ChooseFBConfig(dpy, screen, attrib_list, nelements);
}

XVisualInfo * glXGetVisualFromFBConfig(Display *dpy, GLXFBConfig config)
{
	return gGlxProcs.GetVisualFromFBConfig(dpy, config);
}

Bool glXMakeCurrent(Display *dpy, GLXDrawable drawable, GLXContext ctx)
{
	return gGlxProcs.MakeCurrent(dpy, drawable, ctx);
}

void glXSwapBuffers(Display *dpy, GLXDrawable drawable)
{
	gGlxProcs.SwapBuffers(dpy, drawable);
}

void glXDestroyContext(Display *dpy, GLXContext ctx)
{
	gGlxProcs.DestroyContext(dpy, ctx);
}

GLXContext glXCreateContextAttribsARB(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list)
{
	return gGlxProcs.CreateContextAttribsARB(dpy, config, share_context, direct, attrib_list);
}

}
