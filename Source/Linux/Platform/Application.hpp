#pragma once

#include "Window.hpp"
#include "Key.hpp"

#include <cassert>
#include <stdexcept>
#include <GL3/gl3.h> // Must be included before other GL headers
#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {

/// \brief A Linux application.
class ApplicationT
{
	friend class WindowT;

	private:
	::Display * mDisplay;
	::Atom mWmDeleteWindow;
	::Atom mWmFullScreen;
	::Atom mWmState;
	::XVisualInfo * mVisual;
	::GLXFBConfig * mFramebufferConfigs;
	::XSetWindowAttributes mWindowAttributes;
	::Colormap mColormap;
	::GLXContext mContextId;
	bool mRunning;

	public:
	/// \throws std::runtime_error on error.
	ApplicationT();
	~ApplicationT();
	ApplicationT(ApplicationT &) = delete;
	ApplicationT & operator=(ApplicationT &) = delete;

	/// \brief Run the event loop.
	///
	/// \param Window Object to dispatch events to.
	template<typename T>
	void run(T & Window)
	{
		assert(mRunning == false);

		mRunning = true;
		while (mRunning)  {

			XEvent Event;
			XNextEvent(mDisplay, &Event);
			auto Y = Window.getHeight() - Event.xbutton.y;

			switch (Event.type) {

			case EnterNotify: {
				Window.sendMouseEnterWindow(Event.xmotion.x, Y);
			} break;

			case LeaveNotify: {
				Window.sendMouseLeaveWindow(Event.xmotion.x, Y);
			} break;

			case MotionNotify: {
				Window.sendMouseMotion(Event.xmotion.x, Y);
			} break;

			case ButtonPress: {
				Window.sendButtonPress(Event.xbutton.x, Y, Event.xbutton.button);
			} break;

			case ButtonRelease: {
				Window.sendButtonRelease(Event.xbutton.x, Y, Event.xbutton.button);
			} break;

			case KeyPress: {
				auto Keysym = XLookupKeysym(&Event.xkey, 0);
				Window.sendKeyPress(static_cast<KeyT>(Keysym));
			} break;

			case KeyRelease: {
				auto Keysym = XLookupKeysym(&Event.xkey, 0);
				Window.sendKeyRelease(static_cast<KeyT>(Keysym));
			} break;

			case ConfigureNotify: {
				if (Event.xconfigure.send_event != True) break; // FIXME: Is this correct?
				Window.handleResize(Event.xconfigure.width, Event.xconfigure.height);
			} break;

			case Expose: {
				Window.handleExposed();
			} break;

			case ClientMessage: {
				auto WindowAtom = static_cast<Atom>(Event.xclient.data.l[0]);
				if (WindowAtom == mWmDeleteWindow) Window.handleDeleted();
			} break;

			}

			if (XPending(mDisplay) == 0) Window.update();
		}
	}

	/// \brief Stop the event loop
	void stop();
};

}
}
