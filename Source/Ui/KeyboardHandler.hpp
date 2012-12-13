#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandler
{
	public:
	virtual ~KeyboardHandler() {}
	virtual void handleKeyPress(Platform::Key) {}
	virtual void handleKeyRelease(Platform::Key) {}
};

}
}
