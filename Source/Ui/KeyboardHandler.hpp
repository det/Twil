#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardManagerT;

class KeyboardHandlerT
{
	public:
	virtual ~KeyboardHandlerT() {}

	/// \brief Called on the current handler when a key is pressed.
	virtual void handleKeyPress(KeyboardManagerT &, Platform::KeyT) {}

	/// \brief Called on the current handler when a key is released.
	virtual void handleKeyRelease(KeyboardManagerT &, Platform::KeyT) {}
};

}
}
