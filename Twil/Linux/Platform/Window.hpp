#pragma once

#include "WindowFwd.hpp"

#include "ApplicationFwd.hpp"
#include "GlxFwd.hpp"
#include "X11Fwd.hpp"
#include "Theme/Manager.hpp"
#include "Ui/KeyboardHandlerFwd.hpp"
#include "Ui/MouseHandlerFwd.hpp"
#include "Ui/UnitFwd.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Ui/WindowHandlerFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Platform {

/// \brief A Linux window.

class WindowT
{
	WindowT(WindowT const &) = delete;
	WindowT & operator =(WindowT const &) = delete;

protected:
	ApplicationT * mApplication;
	XWindow mId;
	XColormap mColormap;
	GLXContext mContext;

	/// \brief Swap the front and back buffers.
	void swapBuffers();

public:
	/// \throws std::runtime_error on error.
	WindowT(Ui::WindowBaseT & Window, ApplicationT & Application, Ui::PixelT Width, Ui::PixelT Height);
	~WindowT() noexcept;

	// Documented in Ui::Window
	void show();
	void hide();
	void setFullscreen(bool IsFullScreen);
	void resizePixels(Ui::PixelT Width, Ui::PixelT Height);
	void setTitle(char const * String);
};

}
}
