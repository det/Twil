#pragma once

#include "window.hxx"

#include "application.hxx"
#include "glx.hxx"
#include "x11.hxx"
#include "theme/manager.hxx"
#include "ui/keyboard_handler.hxx"
#include "ui/mouse_handler.hxx"
#include "ui/unit.hxx"
#include "ui/window_base.hxx"
#include "ui/window_handler.hxx"

#include <cstdint>

namespace twil {
namespace platform {

/// \brief A Linux window.

class Window
{
	Window(Window const &) = delete;
	Window & operator =(Window const &) = delete;

protected:
	Application * application_;
	XWindow id_;
	XColormap colormap_;
	GLXContext context_;

	/// \brief Swap the front and back buffers.
	void SwapBuffers();

public:
	/// \throws std::runtime_error on error.
	Window(ui::WindowBase & window, Application & application, ui::Pixel width, ui::Pixel height);
	~Window() noexcept;

	// Documented in ui::Window
	void Show();
	void Hide();
	void SetFullscreen(bool is_fullScreen);
	void ResizePixels(ui::Pixel width, ui::Pixel height);
	void SetTitle(char const * string);
};

}
}
