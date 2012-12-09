#pragma once

#include "Ui/Widget.hpp"
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
			Window.handleMouseEnter(Event.xmotion.x, Event.xmotion.y);
		} break;

		case LeaveNotify: {
			Window.handleMouseLeave(Event.xmotion.x, Event.xmotion.y);
		} break;

		case MotionNotify: {
			Window.handleMouseMotion(Event.xmotion.x, Event.xmotion.y);
		} break;

		case ButtonPress: {
			Window.handleButtonPressed(Event.xbutton.x, Event.xbutton.y, Event.xbutton.button);
		} break;

		case ButtonRelease: {
			Window.handleButtonReleased(Event.xbutton.x, Event.xbutton.y, Event.xbutton.button);
		} break;

		case KeyPress: {
			auto Keysym = XLookupKeysym(&Event.xkey, 0);
			Window.handleKeyPressed((Key) Keysym);
		} break;

		case KeyRelease: {
			auto Keysym = XLookupKeysym(&Event.xkey, 0);
			Window.handleKeyReleased((Key) Keysym);
		} break;

		case ConfigureNotify: {
			assert(Event.xconfigure.width > 0 && Event.xconfigure.width < 65536);
			assert(Event.xconfigure.height > 0 && Event.xconfigure.height < 65536);
			auto Width = static_cast<unsigned short>(Event.xconfigure.width);
			auto Height = static_cast<unsigned short>(Event.xconfigure.height);
			Window.handleResized(Width, Height);
		} break;

		case Expose: {
			if (Event.xexpose.count == 0) Window.handleExposed();
		} break;

		case ClientMessage: {
			if (static_cast<Atom>(Event.xclient.data.l[0]) == mWmDeleteWindow) Window.handleDeleted();
	    } break;

		}

		Window.update();
	}
}

}
}
