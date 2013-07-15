#include "MouseManager.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"

namespace Twil {
namespace Ui {

void MouseManagerT::setHandler(MouseHandlerT & MouseHandler)
{
	mMouseHandler = &MouseHandler;
}

void MouseManagerT::handleMouseEnterWindow(std::int16_t X, std::int16_t Y)
{
	mMouseHandler->handleMouseEnterWindow(X, Y);
}

void MouseManagerT::handleMouseLeaveWindow(std::int16_t X, std::int16_t Y)
{
	mMouseHandler->handleMouseLeaveWindow(X, Y);
}

void MouseManagerT::handleMouseMotion(std::int16_t X, std::int16_t Y)
{
	mMouseHandler->handleMouseMotion(X, Y);
}

void MouseManagerT::handleButtonPress(std::int16_t X, std::int16_t Y , unsigned char Button)
{
	mMouseHandler->handleButtonPress(X, Y, Button);
}

void MouseManagerT::handleButtonRelease(std::int16_t X, std::int16_t Y, unsigned char Button)
{
	mMouseHandler->handleButtonRelease(X, Y, Button);
}

}
}
