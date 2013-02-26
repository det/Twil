#include "Window.hpp"

#include "Application.hpp"
#include "Glx.hpp"

#include <cstring>
#include <stdexcept>

namespace Twil {
namespace Platform {

WindowT::WindowT(ApplicationT & Application) :
	mApplication(Application) // Gcc bug prevents brace initialization syntax here
{

	mId = XCreateWindow(
		mApplication.mDisplay, RootWindow(mApplication.mDisplay, mApplication.mVisual->screen),
		0, 0, 640, 480, 0, mApplication.mVisual->depth, InputOutput, mApplication.mVisual->visual,
		CWBorderPixel | CWColormap | CWEventMask, &mApplication.mWindowAttributes
	);

	if (mId == 0) throw std::runtime_error{"Unable to create window"};

	XStoreName(mApplication.mDisplay, mId, "OpenGL Window");
	XSetWMProtocols(mApplication.mDisplay, mId, &mApplication.mWmDeleteWindow, 1);
	XSync(mApplication.mDisplay, False);

	makeCurrent();
}

WindowT::~WindowT()
{
	XDestroyWindow(mApplication.mDisplay, mId);
}

void WindowT::makeCurrent()
{
	glXMakeCurrent(mApplication.mDisplay, mId, mApplication.mContextId);
}

void WindowT::swapBuffers()
{
	glXSwapBuffers(mApplication.mDisplay, mId);
}

void WindowT::setFullscreen(bool isFullscreen)
{
	::XEvent Event{}; // Zero-initialize
	Event.type = ClientMessage;
	Event.xclient.window = mId;
	Event.xclient.message_type = mApplication.mWmState;
	Event.xclient.format = 32;
	Event.xclient.data.l[0] = isFullscreen ? 1 : 0;
	Event.xclient.data.l[1] = long(mApplication.mWmFullScreen);
	Event.xclient.data.l[2] = 0;
	auto Root = DefaultRootWindow(mApplication.mDisplay);
	XSendEvent(mApplication.mDisplay, Root, False, SubstructureNotifyMask, &Event);
}

void WindowT::show()
{
	XMapWindow(mApplication.mDisplay, mId);
}

void WindowT::hide()
{
	XUnmapWindow(mApplication.mDisplay, mId);
}

void WindowT::resize(unsigned short Width, unsigned short Height)
{
	XResizeWindow(mApplication.mDisplay, mId, Width, Height);
}

void WindowT::setTitle(char const * String)
{
	XStoreName(mApplication.mDisplay, mId, String);
}

}
}
