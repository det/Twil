#include "KeyboardManager.hpp"

#include "KeyboardHandler.hpp"

namespace Twil {
namespace Ui {

void KeyboardManagerT::setHandler(KeyboardHandlerT & Handler)
{
	mHandler = &Handler;
}

void KeyboardManagerT::handleKeyPress(Platform::KeyT Key)
{
	mHandler->handleKeyPress(*this, Key);
}

void KeyboardManagerT::handleKeyRelease(Platform::KeyT Key)
{
	mHandler->handleKeyRelease(*this, Key);
}

}
}
