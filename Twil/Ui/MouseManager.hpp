#pragma once

#include "Platform/Key.hpp"

#include <cstdint>

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

	void handleMouseEnterWindow(float, float);
	void handleMouseLeaveWindow(float, float);
	void handleMouseMotion(float, float);
	void handleButtonPress(float, float, std::uint8_t);
	void handleButtonRelease(float, float, std::uint8_t);
};

}
}
