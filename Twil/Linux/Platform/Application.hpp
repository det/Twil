#pragma once

#include "ApplicationFwd.hpp"

#include "GlxFwd.hpp"
#include "X11Fwd.hpp"
#include "Data/Memory.hpp"
#include "Ui/PixelFwd.hpp"

#include <cassert>
#include <cstdlib>
#include <stdexcept>

namespace Twil {
namespace Platform {

/// \brief A Linux application.
class ApplicationT
{
	friend class WindowT;

	ApplicationT(ApplicationT const &) = delete;
	ApplicationT & operator =(ApplicationT const &) = delete;

private:

public:
	XDisplay * mDisplay;
	XColormap mColormap;
	XContext mContext;
	XAtom mWmDeleteWindow;
	XAtom mWmStateFullscreen;
	XAtom mWmState;
	GLXFBConfig * mConfigs;
	bool mRunning;

public:
	/// \throws std::runtime_error on error.
	ApplicationT();
	~ApplicationT() noexcept;

	Ui::PixelT getMillimeterWidth();
	Ui::PixelT getMillimeterHeight();
	Ui::PixelT getPixelWidth();
	Ui::PixelT getPixelHeight();

	/// \brief Run the event loop
	void run();

	/// \brief Stop the event loop
	void stop();
};

}
}
