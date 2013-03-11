#include "MouseManager.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"

namespace Twil {
namespace Ui {

void MouseManagerT::setHandler(MouseHandlerT & MouseHandler)
{
	mMouseHandler = &MouseHandler;
}

void MouseManagerT::handleMouseEnterWindow(signed short X, signed short Y)
{
	mMouseHandler->handleMouseEnterWindow(X, Y);
}

void MouseManagerT::handleMouseLeaveWindow(signed short X, signed short Y)
{
	mMouseHandler->handleMouseLeaveWindow(X, Y);
}

void MouseManagerT::handleMouseMotion(signed short X, signed short Y)
{
	mMouseHandler->handleMouseMotion(X, Y);
}

void MouseManagerT::handleButtonPress(signed short X, signed short Y , unsigned char Button)
{
	mMouseHandler->handleButtonPress(X, Y, Button);
}

void MouseManagerT::handleButtonRelease(signed short X, signed short Y, unsigned char Button)
{
	mMouseHandler->handleButtonRelease(X, Y, Button);
}

}
}
