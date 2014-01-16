#include "MouseManager.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"

namespace Twil {
namespace Ui {

void MouseManagerT::setHandler(MouseHandlerT & MouseHandler)
{
	mMouseHandler = &MouseHandler;
}

void MouseManagerT::handleMouseEnterWindow(float X, float Y)
{
	mMouseHandler->handleMouseEnterWindow(X, Y);
}

void MouseManagerT::handleMouseLeaveWindow(float X, float Y)
{
	mMouseHandler->handleMouseLeaveWindow(X, Y);
}

void MouseManagerT::handleMouseMotion(float X, float Y)
{
	mMouseHandler->handleMouseMotion(X, Y);
}

void MouseManagerT::handleButtonPress(float X, float Y , std::uint8_t Button)
{
	mMouseHandler->handleButtonPress(X, Y, Button);
}

void MouseManagerT::handleButtonRelease(float X, float Y, std::uint8_t Button)
{
	mMouseHandler->handleButtonRelease(X, Y, Button);
}

}
}
