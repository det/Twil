#include "Ui/WindowBase.hpp"

#include "Ui/KeyboardHandler.hpp"
#include "Ui/MouseHandler.hpp"

namespace Twil {
namespace Ui {

WindowBase::WindowBase(Ui::KeyboardHandler * KeyboardHandler, Ui::MouseHandler * MouseHandler) :
	mKeyboardHandler{KeyboardHandler},
	mMouseHandler{MouseHandler},
	mNeedsRedraw{false},
	mNeedsResize{false}
{}

void WindowBase::setKeyboardHandler(Ui::KeyboardHandler & KeyboardHandler)
{
	mKeyboardHandler = &KeyboardHandler;
}

void WindowBase::setMouseHandler(Ui::MouseHandler & MouseHandler)
{
	mMouseHandler = &MouseHandler;
}

void WindowBase::sendMouseEnterWindow(unsigned short X, unsigned short Y)
{
	mMouseHandler->handleMouseEnterWindow(X, Y);
}

void WindowBase::sendMouseLeaveWindow(unsigned short X, unsigned short Y)
{
	mMouseHandler->handleMouseLeaveWindow(X, Y);
}


void WindowBase::sendKeyPress(Platform::Key Key)
{
	mKeyboardHandler->handleKeyPress(Key);
}

void WindowBase::sendKeyRelease(Platform::Key Key)
{
	mKeyboardHandler->handleKeyRelease(Key);
}

void WindowBase::sendMouseMotion(int X, int Y)
{
	mMouseHandler->handleMouseMotion(X, Y);
}

void WindowBase::sendButtonPress(int X, int Y , unsigned Button)
{
	mMouseHandler->handleButtonPress(X, Y, Button);
}

void WindowBase::sendButtonRelease(int X, int Y, unsigned Button)
{
	mMouseHandler->handleButtonRelease(X, Y, Button);
}

void WindowBase::markNeedsRedraw()
{
	mNeedsRedraw = true;
}

void WindowBase::markNeedsResize()
{
	mNeedsResize = true;
}

}
}
