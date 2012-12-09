#include "Platform/Window.hpp"

#include "Platform/Application.hpp"

#include <cstring>
#include <stdexcept>
#include <GL3/gl3.h> // Must be included before other GL headers
#include <GL/glx.h>
#include <GL/glxext.h>

namespace Twil {
namespace Platform {

Window::Window(Application & application2) :
	mApplication{application2}
{

	mId = XCreateWindow(
		mApplication.mDisplay, RootWindow(mApplication.mDisplay, mApplication.mVisual->screen),
		0, 0, 640, 480, 0, mApplication.mVisual->depth, InputOutput,
		mApplication.mVisual->visual, CWBorderPixel | CWColormap | CWEventMask, &mApplication.mWindowAttributes
	);

	if (mId == 0) throw std::runtime_error{"Unable to create window"};

	XStoreName(mApplication.mDisplay, mId, "OpenGL Window");
	XSetWMProtocols(mApplication.mDisplay, mId, &mApplication.mWmDeleteWindow, 1);
	XSync(mApplication.mDisplay, False);

	makeCurrent();
}

Window::~Window()
{
	XDestroyWindow(mApplication.mDisplay, mId);
}

void Window::makeCurrent()
{
	glXMakeCurrent(mApplication.mDisplay, mId, mApplication.mContextId);
}

void Window::swapBuffers()
{
	glXSwapBuffers(mApplication.mDisplay, mId);
}

void Window::setFullscreen(bool isFullscreen)
{
	::XEvent Event{}; // Zero-initialize
	Event.type = ClientMessage;
	Event.xclient.window = mId;
	Event.xclient.message_type = mApplication.mWmState;
	Event.xclient.format = 32;
	Event.xclient.data.l[0] = isFullscreen ? 1 : 0;
	Event.xclient.data.l[1] = long(mApplication.mWmFullScreen);
	Event.xclient.data.l[2] = 0;
	XSendEvent(mApplication.mDisplay, DefaultRootWindow(mApplication.mDisplay), False, SubstructureNotifyMask, &Event);
}

void Window::show()
{
	XMapWindow(mApplication.mDisplay, mId);
}

void Window::hide()
{
	XUnmapWindow(mApplication.mDisplay, mId);
}

void Window::resize(unsigned short Width, unsigned short Height)
{
	XResizeWindow(mApplication.mDisplay, mId, Width, Height);
}

}
}
