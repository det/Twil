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

	// Let xcb take over event handling
	mConnection = XGetXCBConnection(Display);
	if (mConnection == nullptr) throw std::runtime_error{"Can't get xcb connection from display"};
	XSetEventQueueOwner(Display, XCBOwnsEventQueue);

	// Load atoms
	auto AtomCookie = xcb_intern_atom(mConnection, 0, 4, "ATOM");
	auto NetWmStateCookie = xcb_intern_atom(mConnection, 0, 13, "_NET_WM_STATE");
	auto NetWmStateFullscreenCookie =
		xcb_intern_atom(mConnection, 0, 24, "_NET_WM_STATE_FULLSCREEN");
	auto StringCookie = xcb_intern_atom(mConnection, 0, 6, "STRING");
	auto WmDeleteWindowCookie = xcb_intern_atom(mConnection, 0, 16, "WM_DELETE_WINDOW");
	auto WmNameCookie = xcb_intern_atom(mConnection, 0, 7, "WM_NAME");
	auto WmProtocolsCookie = xcb_intern_atom(mConnection, 0, 12, "WM_PROTOCOLS");

	using ReplyT = std::unique_ptr<xcb_intern_atom_reply_t, Data::FreeDeleterT>;
	ReplyT AtomReply{xcb_intern_atom_reply(mConnection, AtomCookie, nullptr)};
	ReplyT NetWmStateReply{xcb_intern_atom_reply(mConnection, NetWmStateCookie, nullptr)};
	ReplyT NetWmStateFullscreenReply{
		xcb_intern_atom_reply(mConnection, NetWmStateFullscreenCookie, nullptr)};
	ReplyT StringReply{xcb_intern_atom_reply(mConnection, StringCookie, nullptr)};
	ReplyT WmDeleteWindowReply{xcb_intern_atom_reply(mConnection, WmDeleteWindowCookie, nullptr)};
	ReplyT WmNameReply{xcb_intern_atom_reply(mConnection, WmNameCookie, nullptr)};
	ReplyT WmProtocolsReply{xcb_intern_atom_reply(mConnection, WmProtocolsCookie, nullptr)};

	mAtomAtom = AtomReply->atom;
	mNetWmStateAtom = NetWmStateReply->atom;
	mNetWmStateFullscreenAtom = NetWmStateFullscreenReply->atom;
	mStringAtom = StringReply->atom;
	mWmDeleteWindowAtom = WmDeleteWindowReply->atom;
	mWmNameAtom = WmNameReply->atom;
	mWmProtocolsAtom = WmProtocolsReply->atom;
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
