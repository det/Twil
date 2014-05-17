#include "Application.hpp"

#include "Glx.hpp"
#include "SymbolLoader.hpp"
#include "X11.hpp"
#include "Data/ScopeGuard.hpp"
#include "Ui/KeyboardHandler.hpp"
#include "Ui/MouseHandler.hpp"
#include "Ui/WindowBase.hpp"
#include "Ui/WindowHandler.hpp"

#include <iostream>
#include <stdexcept>

namespace Twil {
namespace Platform {

ApplicationT::ApplicationT()
:
	mRunning{false}
{
	mDisplay = XOpenDisplay(0);
	if (mDisplay == nullptr) throw std::runtime_error{"Unable to open display"};
	auto && DisplayGuard = Data::makeScopeGuard([&] { XCloseDisplay(mDisplay); });

	mWmDeleteWindow = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
	mWmStateFullscreen = XInternAtom(mDisplay, "_NET_WM_STATE_FULLSCREEN", False);
	mWmState = XInternAtom(mDisplay, "_NET_WM_STATE", False);
	mContext = XUniqueContext();

	SymbolLoaderT Loader;
	Glx::initialize(Loader);

	static int VisualAttributes[] = {
		GLX_X_RENDERABLE ,					True,
		GLX_DRAWABLE_TYPE,					GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,					GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,					GLX_TRUE_COLOR,
		GLX_RED_SIZE,						8,
		GLX_GREEN_SIZE,						8,
		GLX_BLUE_SIZE,						8,
		GLX_ALPHA_SIZE,						8,
		GLX_DOUBLEBUFFER,					True,
		GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB,	True,
		None};

	int FramebufferCount;
	auto ScreenId = DefaultScreen(mDisplay);

	mConfigs = glXChooseFBConfig(mDisplay, ScreenId, VisualAttributes, &FramebufferCount);
	if (mConfigs == nullptr) throw std::runtime_error{"Unable to find matching video mode"};
	auto && ConfigsGuard = Data::makeScopeGuard([&] { XFree(mConfigs); });

	ConfigsGuard.dismiss();
	DisplayGuard.dismiss();
}

ApplicationT::~ApplicationT() noexcept
{
	XFree(mConfigs);
	XCloseDisplay(mDisplay);
}

std::int16_t ApplicationT::getMillimeterWidth()
{
	return ScreenOfDisplay(mDisplay, DefaultScreen(mDisplay))->mwidth;
}

std::int16_t ApplicationT::getMillimeterHeight()
{
	return ScreenOfDisplay(mDisplay, DefaultScreen(mDisplay))->mheight;
}

std::int16_t ApplicationT::getPixelWidth()
{
	return ScreenOfDisplay(mDisplay, DefaultScreen(mDisplay))->width;
}

std::int16_t ApplicationT::getPixelHeight()
{
	return ScreenOfDisplay(mDisplay, DefaultScreen(mDisplay))->height;
}

void ApplicationT::stop()
{
	mRunning = false;
}

void ApplicationT::run()
{
	assert(mRunning == false);
	mRunning = true;
	XEvent Event;
	while (mRunning)
	{
		XNextEvent(mDisplay, &Event);

		Ui::WindowBaseT * Window;
		auto Ret = XFindContext(
			mDisplay,
			Event.xany.window,
			mContext,
			reinterpret_cast<XPointer *>(&Window));

		if (Ret != 0) continue;

		switch (Event.type)
		{

		case ConfigureNotify:
		{
			Window->handleWindowResize(Event.xconfigure.width, Event.xconfigure.height);
			break;
		}

		case Expose:
		{
			Window->handleWindowExposed();
			break;
		}

		case MotionNotify:
		{
			Window->handleMouseMotion(Event.xmotion.x, Event.xmotion.y);
			break;
		}

		case ButtonPress:
		{
			Window->handleButtonPress(Event.xbutton.x, Event.xbutton.y, Event.xbutton.button);
			break;
		}

		case ButtonRelease:
		{
			Window->handleButtonRelease(Event.xbutton.x, Event.xbutton.y, Event.xbutton.button);
			break;
		}

		case EnterNotify:
		{
			Window->handleMouseEnterWindow(Event.xbutton.x, Event.xbutton.y);
			break;
		}

		case LeaveNotify:
		{
			Window->handleMouseLeaveWindow(Event.xbutton.x, Event.xbutton.y);
			break;
		}

		case ClientMessage:
		{
			if (static_cast<XAtom>(Event.xclient.data.l[0]) == mWmDeleteWindow)
			{
				Window->handleWindowDeleted();
			}
			break;
		}

		}

		Window->handleWindowUpdate();
	}
}


}
}
