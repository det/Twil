#include "Application.hpp"

#include "Glx.hpp"
#include "SymbolLoader.hpp"

#include <stdexcept>

#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>

namespace Twil {
namespace Platform {

ApplicationT::ApplicationT() :
	mRunning{false}
{
	mDisplay = XOpenDisplay(0);
	auto Display = static_cast< ::Display *>(mDisplay);
	if (Display == nullptr) throw std::runtime_error{"Unable to open display"};

	// XXX: port to libxcb
	mStateAtom = XInternAtom(Display, "_NET_WM_STATE", False);
	mStateFullscreenAtom = XInternAtom(Display, "_NET_WM_STATE_FULLSCREEN", False);
	mDeleteWindowAtom = XInternAtom(Display, "WM_DELETE_WINDOW", False);

	// Let xcb take over event handling
	mConnection = XGetXCBConnection(Display);
	if (mConnection == nullptr) throw std::runtime_error{"Can't get xcb connection from display"};
	XSetEventQueueOwner(Display, XCBOwnsEventQueue);
}

ApplicationT::~ApplicationT()
{
	auto Display = static_cast< ::Display *>(mDisplay);
	XCloseDisplay(Display);
}

void ApplicationT::stop()
{
	mRunning = false;
}

}
}
