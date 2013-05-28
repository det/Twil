#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandlerT
{
	public:
	virtual ~KeyboardHandlerT() {}

	/// \brief Called on the current handler when a key is pressed.
	virtual void handleKeyPress(Platform::KeyT) {}

	/// \brief Called on the current handler when a key is released.
	virtual void handleKeyRelease(Platform::KeyT) {}
};

}
}
