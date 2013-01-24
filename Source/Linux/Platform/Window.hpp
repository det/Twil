#pragma once

#include <X11/Xlib.h>

namespace Twil {
namespace Platform {

class ApplicationT;

/// \brief A Linux window.
class WindowT
{
	private:
	ApplicationT & mApplication;
	::Window mId;

	protected:
	/// \brief Make this window the current rendering context.
	void makeCurrent();

	/// \brief Swap the front and back buffers.
	void swapBuffers();

	public:
	/// \throws std::runtime_error on error.
	WindowT(ApplicationT &);
	~WindowT();
	WindowT(WindowT &) = delete;
	WindowT & operator=(WindowT &) = delete;

	/// \brief Show the window.
	void show();

	/// \brief Hide the window.
	void hide();

	/// \brief Set whether the window is fullscreen.
	void setFullscreen(bool IsFullScreen);

	/// \brief Resize the window.
	void resize(unsigned short Width, unsigned short Height);

	/// \brief Set the title.
	void setTitle(char const * String);
};

}
}
