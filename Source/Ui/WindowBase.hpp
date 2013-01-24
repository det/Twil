#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandlerT;
class MouseHandlerT;

/// \brief A base class for widgets to communicate with the Window class
class WindowBaseT
{
	protected:
	KeyboardHandlerT * mKeyboardHandler;
	MouseHandlerT * mMouseHandler;
	bool mNeedsDraw;

	WindowBaseT(KeyboardHandlerT *, MouseHandlerT *);

	public:
	/// \brief Set the keyboard handler.
	void setKeyboardHandler(KeyboardHandlerT &);

	/// \brief Set the mouse handler.
	void setMouseHandler(MouseHandlerT &);

	/// \brief Tell the window a draw is needs to happen.
	void markNeedsDraw();

	void sendMouseEnterWindow(signed short, signed short);
	void sendMouseLeaveWindow(signed short, signed short);
	void sendKeyPress(Platform::KeyT);
	void sendKeyRelease(Platform::KeyT);
	void sendMouseMotion(signed short, signed short);
	void sendButtonPress(signed short, signed short, unsigned char);
	void sendButtonRelease(signed short, signed short, unsigned char);
};

}
}
