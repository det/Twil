#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandler;
class MouseHandler;

class WindowBase
{
	protected:
	Ui::KeyboardHandler * mKeyboardHandler;
	Ui::MouseHandler * mMouseHandler;
	bool mNeedsRedraw;
	bool mNeedsResize;

	WindowBase(Ui::KeyboardHandler *, Ui::MouseHandler *);

	public:
	void setKeyboardHandler(Ui::KeyboardHandler &);
	void setMouseHandler(Ui::MouseHandler &);
	void markNeedsRedraw();
	void markNeedsResize();

	void sendMouseEnterWindow(unsigned short, unsigned short);
	void sendMouseLeaveWindow(unsigned short, unsigned short);
	void sendKeyPress(Platform::Key);
	void sendKeyRelease(Platform::Key);
	void sendMouseMotion(signed short, signed short);
	void sendButtonPress(signed short, signed short, unsigned char);
	void sendButtonRelease(signed short, signed short, unsigned char);
};

}
}
