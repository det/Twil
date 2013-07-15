#pragma once

#include <cstdint>

#include <xcb/xcb.h>

namespace Twil {
namespace Platform {

class ApplicationT;

/// \brief A Linux window.
class WindowT
{
	WindowT(WindowT const &) = delete;
	WindowT & operator =(WindowT const &) = delete;

	private:
	ApplicationT * mApplication;
	xcb_window_t mId;

	// We Use void * here and cast later because including the X11 headers polutes our namespace
	// with all kinds of generically named macros such as "None"
	void * mContext;

	public:
	/// \throws std::runtime_error on error.
	WindowT(ApplicationT &);
	~WindowT();

	/// \brief Make this window the current rendering context.
	void makeCurrent();

	/// \brief Swap the front and back buffers.
	void swapBuffers();

	// Documented in Ui::Window
	void show();
	void hide();
	void setFullscreen(bool IsFullScreen);
	void resize(std::uint16_t Width, std::uint16_t Height);
	void setTitle(char const * String);
};

}
}
