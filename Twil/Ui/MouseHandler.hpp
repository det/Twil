#pragma once

#include <cstdint>

namespace Twil {
namespace Ui {

class MouseHandlerT
{
	public:
	virtual ~MouseHandlerT() {}
	/// \brief Called on the current handler when the pointer is moved.
	virtual void handleMouseMotion(std::int16_t X, std::int16_t Y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void handleButtonPress(std::int16_t X, std::int16_t Y, unsigned char Index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void handleButtonRelease(std::int16_t X, std::int16_t Y, unsigned char Index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void handleMouseLeaveWindow(std::int16_t X, std::int16_t Y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void handleMouseEnterWindow(std::int16_t X, std::int16_t Y) {}
};

}
}
