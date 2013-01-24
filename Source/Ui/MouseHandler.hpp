#pragma once

namespace Twil {
namespace Ui {

class MouseHandlerT
{
	public:
	virtual ~MouseHandlerT() {}
	/// \brief Called on the current handler when the pointer is moved.
	virtual void handleMouseMotion(signed short X, signed short Y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void handleButtonPress(signed short X, signed short Y, unsigned char Index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void handleButtonRelease(signed short X, signed short Y, unsigned char Index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void handleMouseLeaveWindow(signed short X, signed short Y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void handleMouseEnterWindow(signed short X, signed short Y) {}
};

}
}
