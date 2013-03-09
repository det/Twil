#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandlerT;

class KeyboardManagerT
{
	private:
	KeyboardHandlerT * mHandler = nullptr;

	public:
	/// \brief Set the keyboard handler.
	void setHandler(KeyboardHandlerT &);
	void handleKeyPress(Platform::KeyT);
	void handleKeyRelease(Platform::KeyT);
};

}
}
