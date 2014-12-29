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
	auto display = XOpenDisplay(0);
	if (display == nullptr) throw std::runtime_error{"Unable to open display"};
	auto && display_guard = data::MakeScopeGuard([&] { XCloseDisplay(display); });

	wm_delete_window_ = XInternAtom(display, "WM_DELETE_WINDOW", False);
	wm_state_fullscreen_ = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
	wm_state_ = XInternAtom(display, "_NET_WM_STATE", False);
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
	auto screen_id = DefaultScreen(display);

	auto configs = glXChooseFBConfig(display, screen_id, visual_attributes, &num_framebuffers);
	if (configs == nullptr) throw std::runtime_error{"Unable to find matching video mode"};
	auto && configs_guard = data::MakeScopeGuard([&] { XFree(configs); });

	auto info = XRRGetScreenInfo (display, RootWindow(display, DefaultScreen(display)));
	auto && info_guard = data::MakeScopeGuard([&] { XRRFreeScreenConfigInfo(info); });
	Rotation current_rotation;
	SizeID current_size = XRRConfigCurrentConfiguration(info, &current_rotation);
	int nsize;
	auto sizes = XRRConfigSizes(info, &nsize);
	pixel_width_ = sizes[current_size].width;
	pixel_height_ = sizes[current_size].height;
	millimeter_width_ = sizes[current_size].mwidth;
	millimeter_height_ = sizes[current_size].mheight;

	configs_ = configs;
	display_ = display;
	configs_guard.Dismiss();
	display_guard.Dismiss();
}

Application::~Application() noexcept
{
	XFree(configs_);
	XCloseDisplay(display_);
}

ui::Pixel Application::GetPixelWidth()
{
	return pixel_width_;
}

ui::Pixel Application::GetPixelHeight()
{
	return pixel_height_;
}

ui::Pixel Application::GetMillimeterWidth()
{
	return millimeter_width_;
}

ui::Pixel Application::GetMillimeterHeight()
{
	return millimeter_height_;
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
