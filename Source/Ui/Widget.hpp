#pragma once

#include "Platform/Key.hpp"
#include "Ui/Drawable.hpp"

namespace Twil {
namespace Ui {

class Widget : public Drawable {
	public:
	virtual void handleMouseEnter(int, int) = 0;
	virtual void handleMouseLeave(int, int) = 0;
	virtual void handleMouseMotion(int, int) = 0;
	virtual void handleButtonPressed(int, int, unsigned) = 0;
	virtual void handleButtonReleased(int, int, unsigned) = 0;
	virtual void handleKeyPressed(Platform::Key) = 0;
	virtual void handleKeyReleased(Platform::Key) = 0;
};

}
}
