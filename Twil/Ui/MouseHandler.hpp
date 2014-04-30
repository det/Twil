#pragma once

#include "MouseHandlerFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Ui {

class MouseHandlerT
{
public:
	virtual ~MouseHandlerT() = default;
	/// \brief Called on the current handler when the pointer is moved.
	virtual void handleMouseMotion(float X, float Y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void handleButtonPress(float X, float Y, std::uint8_t Index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void handleButtonRelease(float X, float Y, std::uint8_t Index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void handleMouseLeaveWindow(float X, float Y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void handleMouseEnterWindow(float X, float Y) {}
};

}
}
