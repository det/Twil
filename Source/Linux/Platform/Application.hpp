#pragma once

#include "Window.hpp"
#include "Key.hpp"

#include <cassert>
#include <cstdlib>
#include <stdexcept>

#include <xcb/xcb.h>

namespace Twil {
namespace Platform {

/// \brief A Linux application.
class ApplicationT
{
	friend class WindowT;

	private:
	xcb_connection_t * mConnection;

	// We Use void * here and cast later because including the X11 headers polutes our namespace
	// with all kinds of generically named macros such as "None"
	void * mDisplay;

	// XXX: port to use libxcb
	unsigned long mStateAtom;
	unsigned long mStateFullscreenAtom;
	unsigned long mDeleteWindowAtom;

	bool mRunning;

	// Non-copyable
	ApplicationT(ApplicationT &) = delete;
	ApplicationT & operator=(ApplicationT &) = delete;

	public:
	/// \throws std::runtime_error on error.
	ApplicationT();
	~ApplicationT();

	/// \brief Run the event loop.
	///
	/// \param Window Object to dispatch events to.
	template<typename T>
	void run(T & Window)
	{
		assert(mRunning == false);

		mRunning = true;
		while (mRunning)  {
			// We call update on the Window when all queued events have been proccessed
			auto GenericEvent = xcb_poll_for_queued_event(mConnection);
			if (GenericEvent == nullptr) {
				Window.update();
				GenericEvent = xcb_wait_for_event(mConnection);
			}

			switch(GenericEvent->response_type & ~0x80) {

			case XCB_ENTER_NOTIFY: {
				auto Event = reinterpret_cast<xcb_enter_notify_event_t *>(GenericEvent);
				signed short Y = Window.getHeight() - Event->event_y;
				Window.sendMouseEnterWindow(Event->event_x, Y);
			} break;

			case XCB_LEAVE_NOTIFY: {
				auto Event = reinterpret_cast<xcb_leave_notify_event_t *>(GenericEvent);
				signed short Y = Window.getHeight() - Event->event_y;
				Window.sendMouseLeaveWindow(Event->event_x, Y);
			} break;

			case XCB_MOTION_NOTIFY: {
				auto Event = reinterpret_cast<xcb_motion_notify_event_t *>(GenericEvent);
				signed short Y = Window.getHeight() - Event->event_y;
				Window.sendMouseMotion(Event->event_x, Y);
			} break;

			case XCB_BUTTON_PRESS: {
				auto Event = reinterpret_cast<xcb_button_press_event_t *>(GenericEvent);
				signed short Y = Window.getHeight() - Event->event_y;
				Window.sendButtonPress(Event->event_x, Y, Event->detail);
			} break;

			case XCB_BUTTON_RELEASE: {
				auto Event = reinterpret_cast<xcb_button_press_event_t *>(GenericEvent);
				signed short Y = Window.getHeight() - Event->event_y;
				Window.sendButtonRelease(Event->event_x, Y, Event->detail);
			} break;

			case XCB_KEY_PRESS: {
//				auto Keysym = XLookupKeysym(&Event.xkey, 0);
//				Window.sendKeyPress(static_cast<KeyT>(Keysym));
			} break;

			case XCB_KEY_RELEASE: {
//				auto Keysym = XLookupKeysym(&Event.xkey, 0);
//				Window.sendKeyRelease(static_cast<KeyT>(Keysym));
			} break;

			case XCB_CONFIGURE_NOTIFY: {
				auto Event = reinterpret_cast<xcb_configure_notify_event_t *>(GenericEvent);
				Window.handleResize(Event->width, Event->height);
			} break;

			case XCB_EXPOSE: {
				Window.handleExposed();
			} break;

			case XCB_CLIENT_MESSAGE: {
				auto Event = reinterpret_cast<xcb_client_message_event_t *>(GenericEvent);
				auto Atom = Event->data.data32[0];
				if (Atom == mDeleteWindowAtom) Window.handleDeleted();
			} break;

			}

			free(GenericEvent);
		}
	}

	/// \brief Stop the event loop
	void stop();
};

}
}
