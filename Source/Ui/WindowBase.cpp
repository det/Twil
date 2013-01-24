#include "WindowBase.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"

namespace Twil {
namespace Ui {

WindowBaseT::WindowBaseT(KeyboardHandlerT * KeyboardHandler, MouseHandlerT * MouseHandler) :
	mKeyboardHandler{KeyboardHandler},
	mMouseHandler{MouseHandler},
	mNeedsDraw{false}
{}

void WindowBaseT::setKeyboardHandler(KeyboardHandlerT & KeyboardHandler)
{
	mKeyboardHandler = &KeyboardHandler;
}

void WindowBaseT::setMouseHandler(MouseHandlerT & MouseHandler)
{
	mMouseHandler = &MouseHandler;
}

void WindowBaseT::sendMouseEnterWindow(signed short X, signed short Y)
{
	mMouseHandler->handleMouseEnterWindow(X, Y);
}

void WindowBaseT::sendMouseLeaveWindow(signed short X, signed short Y)
{
	mMouseHandler->handleMouseLeaveWindow(X, Y);
}


void WindowBaseT::sendKeyPress(Platform::KeyT Key)
{
	mKeyboardHandler->handleKeyPress(Key);
}

void WindowBaseT::sendKeyRelease(Platform::KeyT Key)
{
	mKeyboardHandler->handleKeyRelease(Key);
}

void WindowBaseT::sendMouseMotion(signed short X, signed short Y)
{
	mMouseHandler->handleMouseMotion(X, Y);
}

void WindowBaseT::sendButtonPress(signed short X, signed short Y , unsigned char Button)
{
	mMouseHandler->handleButtonPress(X, Y, Button);
}

void WindowBaseT::sendButtonRelease(signed short X, signed short Y, unsigned char Button)
{
	mMouseHandler->handleButtonRelease(X, Y, Button);
}

void WindowBaseT::markNeedsDraw()
{
	mNeedsDraw = true;
}

}
}
