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
	virtual void handleMouseMotion(std::int32_t X, std::int32_t Y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void handleButtonPress(std::int32_t X, std::int32_t Y, std::uint8_t Index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void handleButtonRelease(std::int32_t X, std::int32_t Y, std::uint8_t Index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void handleMouseLeaveWindow(std::int32_t X, std::int32_t Y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void handleMouseEnterWindow(std::int32_t X, std::int32_t Y) {}
};

}
}
