#pragma once

namespace Twil {
namespace Ui {

class MouseHandler
{
	public:
	virtual ~MouseHandler() {}
	virtual void handleMouseMotion(signed short, signed short) {}
	virtual void handleButtonPress(signed short, signed short, unsigned char) {}
	virtual void handleButtonRelease(signed short, signed short, unsigned char) {}
	virtual void handleMouseLeaveWindow(signed short, signed short) {}
	virtual void handleMouseEnterWindow(signed short, signed short) {}
};

}
}
