#include "Window.hpp"

#include "Application.hpp"
#include "Glx.hpp"
#include "SymbolLoader.hpp"
#include "X11.hpp"
#include "Data/ScopeGuard.hpp"
#include "Gl/Context.hpp"

#include <cstring>
#include <cstdint>
#include <stdexcept>

namespace Twil {
namespace Platform {

WindowT::WindowT(Ui::WindowBaseT & Window, ApplicationT & Application, std::int16_t Width, std::int16_t Height)
:
	mApplication{&Application}
{
	auto Display = mApplication->mDisplay;
	auto & Config = mApplication->mConfigs[0];

	auto VisualInfo = glXGetVisualFromFBConfig(Display, Config);
	if (VisualInfo == nullptr) throw std::runtime_error{"Unable to obtain VisualInfo"};
	auto && VisualInfoGuard = Data::makeScopeGuard([&] { XFree(VisualInfo); });

	mColormap = XCreateColormap(
		Display,
		RootWindow(Display, VisualInfo->screen),
		VisualInfo->visual, AllocNone);
	auto && ColormapGuard = Data::makeScopeGuard([&] { XFreeColormap(Display, mColormap); });

	XSetWindowAttributes WindowAttributes;
	WindowAttributes.colormap = mColormap;
	WindowAttributes.background_pixmap = None;
	WindowAttributes.border_pixel = 0;
	WindowAttributes.event_mask =
		EnterWindowMask |
		LeaveWindowMask |
		PointerMotionMask |
		ButtonPressMask |
		ButtonReleaseMask |
		KeyPressMask |
		KeyReleaseMask |
		StructureNotifyMask |
		ExposureMask;

	mId = XCreateWindow(
		Display,
		RootWindow(Display, VisualInfo->screen),
		0, 0, Width, Height, 0, VisualInfo->depth, InputOutput,
		VisualInfo->visual,
		CWBorderPixel | CWColormap | CWEventMask, &WindowAttributes);
	auto && WindowGuard = Data::makeScopeGuard([&] { XDestroyWindow(Display, mId); });

	XSaveContext(Display, mId, mApplication->mContext, reinterpret_cast<XPointer>(&Window));
	auto && SaveContextGuard = Data::makeScopeGuard([&] { XDeleteContext(Display, mId, mApplication->mContext); });

	XSetWMProtocols(Display, mId, &mApplication->mWmDeleteWindow, 1);
	XStoreName(Display, mId, "Twil Window");
	XMapWindow(Display, mId);

	int ContextAttribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 3,
		None};

	mContext = glXCreateContextAttribsARB(Display, Config, 0, True, ContextAttribs);
	if (mContext == 0) throw std::runtime_error{"Unable to create OpenGL context"};
	auto && ContextGuard = Data::makeScopeGuard([&] { glXDestroyContext(Display, mContext); });

	glXMakeCurrent(Display, mId, mContext);
	SymbolLoaderT Loader;
	Gl::Context::initialize(Loader);

	SaveContextGuard.dismiss();
	ContextGuard.dismiss();
	WindowGuard.dismiss();
	ColormapGuard.dismiss();
}

WindowT::~WindowT() noexcept
{
	auto Display = mApplication->mDisplay;

	XDeleteContext(Display, mId, mApplication->mContext);
	glXDestroyContext(Display, mContext);
	XDestroyWindow(Display, mId);
	XFreeColormap(Display, mColormap);
}

void WindowT::swapBuffers()
{
	auto Display = mApplication->mDisplay;
	glXSwapBuffers(Display, mId);
}

void WindowT::setFullscreen(bool IsFullscreen)
{
	auto Display = mApplication->mDisplay;
	XEvent Event{};
	Event.type = ClientMessage;
	Event.xclient.window = mId;
	Event.xclient.message_type = mApplication->mWmState;
	Event.xclient.format = 32;
	Event.xclient.data.l[0] = IsFullscreen;
	Event.xclient.data.l[1] = mApplication->mWmStateFullscreen;
	Event.xclient.data.l[2] = None;
	XSendEvent(Display, DefaultRootWindow(Display), False, SubstructureNotifyMask, &Event);
}

void WindowT::show()
{
	auto Display = mApplication->mDisplay;
	XMapWindow(Display, mId);
}

void WindowT::hide()
{
	auto Display = mApplication->mDisplay;
	XUnmapWindow(Display, mId);
}

void WindowT::resizePixels(std::int16_t Width, std::int16_t Height)
{
	auto Display = mApplication->mDisplay;
	XResizeWindow(Display, mId, Width, Height);
}

void WindowT::setTitle(char const * String)
{
	auto Display = mApplication->mDisplay;
	XStoreName(Display, mId, String);
}

}
}
