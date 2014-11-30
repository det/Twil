#pragma once

#include "keyboard_handler.hxx"

#include "platform/key.hpp"

namespace twil {
namespace ui {

class KeyboardHandler
{
public:
	virtual ~KeyboardHandler() = default;

	/// \brief Called on the current handler when a key is pressed.
	virtual void HandleKeyPress(platform::Key) {}

	/// \brief Called on the current handler when a key is released.
	virtual void HandleKeyRelease(platform::Key) {}
};

}
}
