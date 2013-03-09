#pragma once

namespace Twil {
namespace Ui {

class MouseManagerT;

class MouseHandlerT
{
	public:
	virtual ~MouseHandlerT() {}
	/// \brief Called on the current handler when the pointer is moved.
	virtual void handleMouseMotion(MouseManagerT &, signed short X, signed short Y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void handleButtonPress(MouseManagerT &, signed short X, signed short Y, unsigned char Index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void handleButtonRelease(MouseManagerT &, signed short X, signed short Y, unsigned char Index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void handleMouseLeaveWindow(MouseManagerT &, signed short X, signed short Y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void handleMouseEnterWindow(MouseManagerT &, signed short X, signed short Y) {}
};

}
}
