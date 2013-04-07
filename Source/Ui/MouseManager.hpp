#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandlerT;
class MouseHandlerT;

/// \brief A base class for widgets to communicate with the Window class
class MouseManagerT
{
	MouseManagerT(MouseManagerT const &) = delete;
	MouseManagerT & operator =(MouseManagerT const &) = delete;

	private:
	MouseHandlerT * mMouseHandler = nullptr;

	public:
	MouseManagerT() = default;

	/// \brief Set the mouse handler.
	void setHandler(MouseHandlerT &);

	void handleMouseEnterWindow(signed short, signed short);
	void handleMouseLeaveWindow(signed short, signed short);
	void handleMouseMotion(signed short, signed short);
	void handleButtonPress(signed short, signed short, unsigned char);
	void handleButtonRelease(signed short, signed short, unsigned char);
};

}
}
