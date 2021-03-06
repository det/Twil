#pragma once

#include "application.hxx"

#include "glx.hxx"
#include "window.hxx"
#include "x11.hxx"
#include "ui/unit.hxx"

#include <cassert>
#include <cstdlib>
#include <memory>
#include <stdexcept>

namespace twil {
namespace platform {

/// \brief A Linux application.
class Application
{
	friend Window;

	Application(Application const &) = delete;
	Application & operator =(Application const &) = delete;

private:

public:
	XDisplay * display_;
	XColormap colormap_;
	XContext context_;
	XAtom wm_delete_window_;
	XAtom wm_state_fullscreen_;
	XAtom wm_state_;
	GLXFBConfig * configs_;
	ui::Pixel pixel_width_;
	ui::Pixel pixel_height_;
	ui::Pixel millimeter_width_;
	ui::Pixel millimeter_height_;
	bool running_;

public:
	/// \throws std::runtime_error on error.
	Application();
	~Application() noexcept;

	ui::Pixel GetPixelWidth();
	ui::Pixel GetPixelHeight();
	ui::Pixel GetMillimeterWidth();
	ui::Pixel GetMillimeterHeight();

	/// \brief Run the event loop
	void Run();

	/// \brief Stop the event loop
	void Stop();
};

}
}
