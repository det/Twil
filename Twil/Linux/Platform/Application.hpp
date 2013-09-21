#pragma once

#include "Key.hpp"
#include "Window.hpp"
#include "Data/Memory.hpp"

#include <cassert>
#include <cstdlib>
#include <stdexcept>

#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>

namespace Twil {
namespace Platform {

class KeySymbolsT
{
private:
	xcb_key_symbols_t * mPointer;

public:
	KeySymbolsT(xcb_connection_t * Connection)
	:
		mPointer{xcb_key_symbols_alloc(Connection)}
	{}

	~KeySymbolsT()
	{
		xcb_key_symbols_free(mPointer);
	}

	operator xcb_key_symbols_t *()
	{
		return mPointer;
	}
};

/// \brief A Linux application.
class ApplicationT
{
	friend class WindowT;

	ApplicationT(ApplicationT const &) = delete;
	ApplicationT & operator =(ApplicationT const &) = delete;

private:
	xcb_connection_t * mConnection;

	// We Use void * here and cast later because including the X11 headers polutes our namespace
	// with all kinds of generically named macros such as "None"
	void * mDisplay;

	xcb_atom_t mAtomAtom;
	xcb_atom_t mNetWmStateAtom;
	xcb_atom_t mNetWmStateFullscreenAtom;
	xcb_atom_t mStringAtom;
	xcb_atom_t mWmDeleteWindowAtom;
	xcb_atom_t mWmNameAtom;
	xcb_atom_t mWmProtocolsAtom;

	bool mRunning;

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

//		KeySymbolsT KeySymbols{mConnection};
		auto & MouseManager = Window.getMouseManager();
//		auto & KeyboardManager = Window.getKeyboardManager();

		mRunning = true;
		while (mRunning)
		{
			// We call update on the Window when all queued events have been proccessed
			auto GenericEvent = xcb_poll_for_queued_event(mConnection);
			if (GenericEvent == nullptr) 
			{
				Window.update();
				GenericEvent = xcb_wait_for_event(mConnection);
			}

			// Ensure the pointer gets free'd
			std::unique_ptr<xcb_generic_event_t, Data::FreeDeleterT> EventPointer{GenericEvent};

			switch(EventPointer->response_type & ~0x80)
			{

			case XCB_ENTER_NOTIFY:
			{
				auto Event = reinterpret_cast<xcb_enter_notify_event_t *>(GenericEvent);
				std::int16_t Y = Window.getHeight() - Event->event_y;
				MouseManager.handleMouseEnterWindow(Event->event_x, Y);
			} break;

			case XCB_LEAVE_NOTIFY:
			{
				auto Event = reinterpret_cast<xcb_leave_notify_event_t *>(GenericEvent);
				std::int16_t Y = Window.getHeight() - Event->event_y;
				MouseManager.handleMouseLeaveWindow(Event->event_x, Y);
			} break;

			case XCB_MOTION_NOTIFY:
			{
				auto Event = reinterpret_cast<xcb_motion_notify_event_t *>(GenericEvent);
				std::int16_t Y = Window.getHeight() - Event->event_y;
				MouseManager.handleMouseMotion(Event->event_x, Y);
			} break;

			case XCB_BUTTON_PRESS:
			{
				auto Event = reinterpret_cast<xcb_button_press_event_t *>(GenericEvent);
				std::int16_t Y = Window.getHeight() - Event->event_y;
				MouseManager.handleButtonPress(Event->event_x, Y, Event->detail);
			} break;

			case XCB_BUTTON_RELEASE:
			{
				auto Event = reinterpret_cast<xcb_button_press_event_t *>(GenericEvent);
				std::int16_t Y = Window.getHeight() - Event->event_y;
				MouseManager.handleButtonRelease(Event->event_x, Y, Event->detail);
			} break;

			case XCB_KEY_PRESS:
			{
//				auto Event = reinterpret_cast<xcb_key_press_event_t *>(GenericEvent);
//				auto Keysym = xcb_key_press_lookup_keysym(KeySymbols, Event, 0);
			} break;

			case XCB_KEY_RELEASE: {
//				auto Event = reinterpret_cast<xcb_key_release_event_t *>(GenericEvent);
//				auto Keysym = xcb_key_release_lookup_keysym(KeySymbols, Event, 0);
			} break;

			case XCB_CONFIGURE_NOTIFY:
			{
				auto Event = reinterpret_cast<xcb_configure_notify_event_t *>(GenericEvent);
				Window.handleResize(Event->width, Event->height);
			} break;

			case XCB_EXPOSE:
			{
				Window.handleExposed();				
			} break;

			case XCB_CLIENT_MESSAGE:
			{
				auto Event = reinterpret_cast<xcb_client_message_event_t *>(GenericEvent);
				auto Atom = Event->data.data32[0];
				if (Atom == mWmDeleteWindowAtom) Window.handleDeleted();
			} break;


			}
		}
	}

	/// \brief Stop the event loop
	void stop();
};

}
}
