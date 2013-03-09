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
	mMouseHandler->handleMouseEnterWindow(*this, X, Y);
}

void MouseManagerT::handleMouseLeaveWindow(signed short X, signed short Y)
{
	mMouseHandler->handleMouseLeaveWindow(*this, X, Y);
}

void MouseManagerT::handleMouseMotion(signed short X, signed short Y)
{
	mMouseHandler->handleMouseMotion(*this, X, Y);
}

void MouseManagerT::handleButtonPress(signed short X, signed short Y , unsigned char Button)
{
	mMouseHandler->handleButtonPress(*this, X, Y, Button);
}

void MouseManagerT::handleButtonRelease(signed short X, signed short Y, unsigned char Button)
{
	mMouseHandler->handleButtonRelease(*this, X, Y, Button);
}

}
}
