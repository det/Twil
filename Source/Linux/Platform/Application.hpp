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

	template<typename T>
	void run(T &);
	void stop();
};

template<typename T>
void Application::run(T & Window)
{
	mRunning = true;
	while (mRunning)  {
		XEvent Event;
		XNextEvent(mDisplay, &Event);

		switch (Event.type) {

		case EnterNotify: {
			Window.sendMouseEnterWindow(Event.xmotion.x,  Window.getHeight() - Event.xmotion.y);
		} break;

		case LeaveNotify: {
			Window.sendMouseLeaveWindow(Event.xmotion.x,  Window.getHeight() - Event.xmotion.y);
		} break;

		case MotionNotify: {
			Window.sendMouseMotion(Event.xmotion.x,  Window.getHeight() - Event.xmotion.y);
		} break;

		case ButtonPress: {
			Window.sendButtonPress(Event.xbutton.x,  Window.getHeight() - Event.xbutton.y, Event.xbutton.button);
		} break;

		case ButtonRelease: {
			Window.sendButtonRelease(Event.xbutton.x, Window.getHeight() - Event.xbutton.y, Event.xbutton.button);
		} break;

		case KeyPress: {
			auto Keysym = XLookupKeysym(&Event.xkey, 0);
			Window.sendKeyPress((Key) Keysym);
		} break;

		case KeyRelease: {
			auto Keysym = XLookupKeysym(&Event.xkey, 0);
			Window.sendKeyRelease((Key) Keysym);
		} break;

		case ConfigureNotify: {
			Window.handleResize(Event.xconfigure.width, Event.xconfigure.height);
		} break;

		case Expose: {
			if (Event.xexpose.count == 0) Window.handleExposed();
		} break;

		case ClientMessage: {
			if (static_cast<Atom>(Event.xclient.data.l[0]) == mWmDeleteWindow) Window.handleDeleted();
		} break;

		}

		if (XPending(mDisplay) == 0) Window.update();
	}
}

}
}
