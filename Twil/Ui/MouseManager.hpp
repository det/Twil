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

	void handleMouseEnterWindow(std::int16_t, std::int16_t);
	void handleMouseLeaveWindow(std::int16_t, std::int16_t);
	void handleMouseMotion(std::int16_t, std::int16_t);
	void handleButtonPress(std::int16_t, std::int16_t, unsigned char);
	void handleButtonRelease(std::int16_t, std::int16_t, unsigned char);
};

}
}
