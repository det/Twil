#pragma once

#include "Platform/Key.hpp"

namespace Twil {
namespace Ui {

class KeyboardHandlerT;

class KeyboardManagerT
{
	KeyboardManagerT(KeyboardManagerT const &) = delete;
	KeyboardManagerT & operator =(KeyboardManagerT const &) = delete;

	private:
	KeyboardHandlerT * mHandler = nullptr;

	public:
	KeyboardManagerT() = default;

	/// \brief Set the keyboard handler.
	void setHandler(KeyboardHandlerT &);

	void handleKeyPress(Platform::KeyT);
	void handleKeyRelease(Platform::KeyT);
};

}
}
