#pragma once

#include "MouseHandlerFwd.hpp"
#include "DipFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Ui {

class MouseHandlerT
{
public:
	virtual ~MouseHandlerT() = default;
	/// \brief Called on the current handler when the pointer is moved.
	virtual void handleMouseMotion(DipT X, DipT Y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void handleButtonPress(DipT X, DipT Y, std::uint8_t Index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void handleButtonRelease(DipT X, DipT Y, std::uint8_t Index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void handleMouseLeaveWindow(DipT X, DipT Y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void handleMouseEnterWindow(DipT X, DipT Y) {}
};

}
}
