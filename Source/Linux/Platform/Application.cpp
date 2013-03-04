#include "Application.hpp"

#include "Glx.hpp"
#include "FreeDeleter.hpp"
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

	// Let xcb take over event handling
	mConnection = XGetXCBConnection(Display);
	if (mConnection == nullptr) throw std::runtime_error{"Can't get xcb connection from display"};
	XSetEventQueueOwner(Display, XCBOwnsEventQueue);

	// Load atoms
	auto NetWmStateCookie = xcb_intern_atom(mConnection, 0, 13, "_NET_WM_STATE");
	auto NetWmStateFullscreenCookie = xcb_intern_atom(mConnection, 0, 24, "_NET_WM_STATE_FULLSCREEN");
	auto StringCookie = xcb_intern_atom(mConnection, 0, 6, "STRING");
	auto WmDeleteWindowCookie = xcb_intern_atom(mConnection, 0, 16, "WM_DELETE_WINDOW");
	auto WmNameCookie = xcb_intern_atom(mConnection, 0, 7, "WM_NAME");

	std::unique_ptr<xcb_intern_atom_reply_t, FreeDeleterT> NetWmStateReply{
		xcb_intern_atom_reply(mConnection, NetWmStateCookie, nullptr)
	};
	std::unique_ptr<xcb_intern_atom_reply_t, FreeDeleterT> NetWmStateFullscreenReply{
		xcb_intern_atom_reply(mConnection, NetWmStateFullscreenCookie, nullptr)
	};
	std::unique_ptr<xcb_intern_atom_reply_t, FreeDeleterT> StringReply{
		xcb_intern_atom_reply(mConnection, StringCookie, nullptr)
	};
	std::unique_ptr<xcb_intern_atom_reply_t, FreeDeleterT> WmDeleteWindowReply{
		xcb_intern_atom_reply(mConnection, WmDeleteWindowCookie, nullptr)
	};
	std::unique_ptr<xcb_intern_atom_reply_t, FreeDeleterT> WmNameReply{
		xcb_intern_atom_reply(mConnection, WmNameCookie, nullptr)
	};

	mNetWmStateAtom = NetWmStateReply->atom;
	mNetWmStateFullscreenAtom = NetWmStateFullscreenReply->atom;
	mStringAtom = StringReply->atom;
	mWmDeleteWindowAtom = WmDeleteWindowReply->atom;
	mWmNameAtom = WmNameReply->atom;
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
