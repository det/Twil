#include "application.hpp"

#include "symbol_loader.hpp"
#include "data/scope_guard.hpp"
#include "ui/keyboard_handler.hpp"
#include "ui/mouse_handler.hpp"
#include "ui/window_base.hpp"
#include "ui/window_handler.hpp"

#include <iostream>
#include <stdexcept>

// These headers define many poorly named macros, include last
#include "glx.hpp"
#include "x11.hpp"

namespace twil {
namespace platform {

Application::Application()
:
	running_{false}
{
	display_ = XOpenDisplay(0);
	if (display_ == nullptr) throw std::runtime_error{"Unable to open display"};
	auto && display_guard = data::MakeScopeGuard([&] { XCloseDisplay(display_); });

	wm_delete_window_ = XInternAtom(display_, "WM_DELETE_WINDOW", False);
	wm_state_fullscreen_ = XInternAtom(display_, "_NET_WM_STATE_FULLSCREEN", False);
	wm_state_ = XInternAtom(display_, "_NET_WM_STATE", False);
	context_ = XUniqueContext();

	SymbolLoader loader;
	glx::Initialize(loader);

	static int visual_attributes[] = {
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

	int num_framebuffers;
	auto screen_id = DefaultScreen(display_);

	configs_ = glXChooseFBConfig(display_, screen_id, visual_attributes, &num_framebuffers);
	if (configs_ == nullptr) throw std::runtime_error{"Unable to find matching video mode"};
	auto && configs_guard = data::MakeScopeGuard([&] { XFree(configs_); });

	configs_guard.Dismiss();
	display_guard.Dismiss();
}

Application::~Application() noexcept
{
	XFree(configs_);
	XCloseDisplay(display_);
}

ui::Pixel Application::GetMillimeterWidth()
{
	return ScreenOfDisplay(display_, DefaultScreen(display_))->mwidth;
}

ui::Pixel Application::GetMillimeterHeight()
{
	return ScreenOfDisplay(display_, DefaultScreen(display_))->mheight;
}

ui::Pixel Application::GetPixelWidth()
{
	return ScreenOfDisplay(display_, DefaultScreen(display_))->width;
}

ui::Pixel Application::GetPixelHeight()
{
	return ScreenOfDisplay(display_, DefaultScreen(display_))->height;
}

void Application::Stop()
{
	running_ = false;
}

void Application::Run()
{
	assert(running_ == false);
	running_ = true;
	XEvent event;
	while (running_)
	{
		XNextEvent(display_, &event);

		ui::WindowBase * window;
		auto res = XFindContext(
			display_,
			event.xany.window,
			context_,
			reinterpret_cast<XPointer *>(&window));

		if (res != 0) continue;

		switch (event.type)
		{

		case ConfigureNotify:
		{
			window->HandleWindowResize(event.xconfigure.width, event.xconfigure.height);
			break;
		}

		case Expose:
		{
			window->HandleWindowExposed();
			break;
		}

		case MotionNotify:
		{
			window->HandleMouseMotion(event.xmotion.x, event.xmotion.y);
			break;
		}

		case ButtonPress:
		{
			window->HandleButtonPress(event.xbutton.x, event.xbutton.y, event.xbutton.button);
			break;
		}

		case ButtonRelease:
		{
			window->HandleButtonRelease(event.xbutton.x, event.xbutton.y, event.xbutton.button);
			break;
		}

		case EnterNotify:
		{
			window->HandleMouseEnterWindow(event.xbutton.x, event.xbutton.y);
			break;
		}

		case LeaveNotify:
		{
			window->HandleMouseLeaveWindow(event.xbutton.x, event.xbutton.y);
			break;
		}

		case ClientMessage:
		{
			if (static_cast<XAtom>(event.xclient.data.l[0]) == wm_delete_window_)
			{
				window->HandleWindowDeleted();
			}
			break;
		}

		}

		window->HandleWindowUpdate();
	}
}


}
}
