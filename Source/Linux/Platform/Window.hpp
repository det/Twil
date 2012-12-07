#pragma once

#include <X11/Xlib.h>

namespace Twil {
namespace Platform {

class Application;

class Window {
	private:
	Platform::Application & mApplication;
	::Window mId;

	public:
	Window(Platform::Application &);
	~Window();
	Window(Platform::Window &) = delete;
	Window & operator=(Platform::Window &) = delete;

	void makeCurrent();
	void swapBuffers();
	void setFullscreen(bool);
};

}
}
