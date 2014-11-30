#pragma once

#include "mouse_handler.hxx"
#include "unit.hxx"

#include <cstdint>

namespace twil {
namespace ui {

class MouseHandler
{
public:
	virtual ~MouseHandler() = default;
	/// \brief Called on the current handler when the pointer is moved.
	virtual void HandleMouseMotion(Dip x, Dip y) {}

	/// \brief Called on the current handler when a mouse button is clicked.
	virtual void HandleButtonPress(Dip x, Dip y, std::uint8_t index) {}

	/// \brief Called on the current handler when a mouse button is released.
	virtual void HandleButtonRelease(Dip x, Dip y, std::uint8_t index) {}

	/// \brief Called on the current handler when the pointer leaves the window.
	virtual void HandleMouseLeaveWindow(Dip x, Dip y) {}

	/// \brief Called on the current handler when the pointer enters the window.
	virtual void HandleMouseEnterWindow(Dip x, Dip y) {}
};

}
}
