#include "window.hpp"

#include "application.hpp"
#include "symbol_loader.hpp"
#include "data/scope_guard.hpp"
#include "gl/context.hpp"

#include <cstring>
#include <cstdint>
#include <iostream>
#include <string>
#include <stdexcept>

// These headers define many poorly named macros, include last
#include "glx.hpp"
#include "x11.hpp"

#ifndef NDEBUG
namespace {

void HandleDebug(
	GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, GLchar const * message, void * user_param)
{
	std::cerr.write(message, length);
}

}
#endif

namespace twil {
namespace platform {

Window::Window(ui::WindowBase & window, Application & application, ui::Pixel width, ui::Pixel height)
:
	application_{&application}
{
	auto display = application_->display_;
	auto & config = application_->configs_[0];

	auto visual_info = glXGetVisualFromFBConfig(display, config);
	if (visual_info == nullptr) throw std::runtime_error{"Unable to obtain VisualInfo"};
	auto && visual_info_guard = data::MakeScopeGuard([&] { XFree(visual_info); });

	colormap_ = XCreateColormap(
		display,
		RootWindow(display, visual_info->screen),
		visual_info->visual, AllocNone);
	auto && colormap_guard = data::MakeScopeGuard([&] { XFreeColormap(display, colormap_); });

	XSetWindowAttributes window_attributes;
	window_attributes.colormap = colormap_;
	window_attributes.background_pixmap = None;
	window_attributes.border_pixel = 0;
	window_attributes.event_mask =
		EnterWindowMask |
		LeaveWindowMask |
		PointerMotionMask |
		ButtonPressMask |
		ButtonReleaseMask |
		KeyPressMask |
		KeyReleaseMask |
		StructureNotifyMask |
		ExposureMask;

	id_ = XCreateWindow(
		display,
		RootWindow(display, visual_info->screen),
		0, 0, width, height, 0, visual_info->depth, InputOutput,
		visual_info->visual,
		CWBorderPixel | CWColormap | CWEventMask, &window_attributes);
	auto && window_guard = data::MakeScopeGuard([&] { XDestroyWindow(display, id_); });

	XSaveContext(display, id_, application_->context_, reinterpret_cast<XPointer>(&window));
	auto && save_context_guard = data::MakeScopeGuard([&] { XDeleteContext(display, id_, application_->context_); });

	XSetWMProtocols(display, id_, &application_->wm_delete_window_, 1);
	XStoreName(display, id_, "Twil Window");
	XMapWindow(display, id_);

	int ContextAttribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 3,
#ifndef NDEBUG
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
#endif
		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None};

	context_ = glXCreateContextAttribsARB(display, config, 0, True, ContextAttribs);
	if (context_ == 0) throw std::runtime_error{"Unable to create OpenGL context"};
	auto && context_guard = data::MakeScopeGuard([&] { glXDestroyContext(display, context_); });

	glXMakeCurrent(display, id_, context_);
	SymbolLoader loader;
	gl::context::Initialize(loader);

#ifndef NDEBUG
	glDebugMessageCallbackARB(HandleDebug, nullptr);
#endif

	save_context_guard.Dismiss();
	context_guard.Dismiss();
	window_guard.Dismiss();
	colormap_guard.Dismiss();
}

Window::~Window() noexcept
{
	auto display = application_->display_;
	XDeleteContext(display, id_, application_->context_);
	glXDestroyContext(display, context_);
	XDestroyWindow(display, id_);
	XFreeColormap(display, colormap_);
}

void Window::SwapBuffers()
{
	glXSwapBuffers(application_->display_, id_);
}

void Window::SetFullscreen(bool is_fullscreen)
{
	XEvent event{};
	event.type = ClientMessage;
	event.xclient.window = id_;
	event.xclient.message_type = application_->wm_state_;
	event.xclient.format = 32;
	event.xclient.data.l[0] = is_fullscreen;
	event.xclient.data.l[1] = application_->wm_state_fullscreen_;
	event.xclient.data.l[2] = None;
	auto display = application_->display_;
	XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask, &event);
}

void Window::Show()
{
	XMapWindow(application_->display_, id_);
}

void Window::Hide()
{
	XUnmapWindow(application_->display_, id_);
}

void Window::ResizePixels(ui::Pixel width, ui::Pixel height)
{
	XResizeWindow(application_->display_, id_, width, height);
}

void Window::SetTitle(char const * string)
{
	XStoreName(application_->display_, id_, string);
}

}
}
