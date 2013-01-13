#pragma once

#include "Platform/Window.hpp"
#include "Platform/Key.hpp"

#include <cassert>
#include <stdexcept>
#include <GL3/gl3.h> // Must be included before other GL headers
#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {

class Application
{
	friend class Platform::Window;

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
	Application();
	~Application();
	Application(Application &) = delete;
	Application & operator=(Application &) = delete;

	void stop();

	template<typename T>
	void run(T & Object)
	{
		mRunning = true;
		while (mRunning)  {
			XEvent Event;
			XNextEvent(mDisplay, &Event);

			switch (Event.type) {

			case EnterNotify: {
				Object.sendMouseEnterWindow(Event.xmotion.x,  Object.getHeight() - Event.xmotion.y);
			} break;

			case LeaveNotify: {
				Object.sendMouseLeaveWindow(Event.xmotion.x,  Object.getHeight() - Event.xmotion.y);
			} break;

			case MotionNotify: {
				Object.sendMouseMotion(Event.xmotion.x,  Object.getHeight() - Event.xmotion.y);
			} break;

			case ButtonPress: {
				Object.sendButtonPress(Event.xbutton.x,  Object.getHeight() - Event.xbutton.y, Event.xbutton.button);
			} break;

			case ButtonRelease: {
				Object.sendButtonRelease(Event.xbutton.x, Object.getHeight() - Event.xbutton.y, Event.xbutton.button);
			} break;

			case KeyPress: {
				auto Keysym = XLookupKeysym(&Event.xkey, 0);
				Object.sendKeyPress((Key) Keysym);
			} break;

			case KeyRelease: {
				auto Keysym = XLookupKeysym(&Event.xkey, 0);
				Object.sendKeyRelease((Key) Keysym);
			} break;

			case ConfigureNotify: {
				Object.handleResize(Event.xconfigure.width, Event.xconfigure.height);
			} break;

			case Expose: {
				if (Event.xexpose.count == 0) Object.handleExposed();
			} break;

			case ClientMessage: {
				if (static_cast<Atom>(Event.xclient.data.l[0]) == mWmDeleteWindow) Object.handleDeleted();
			} break;

			}

			if (XPending(mDisplay) == 0) Object.update();
		}
	}

};

}
}
