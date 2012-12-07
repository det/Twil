#include "Ui/WindowControl.hpp"

namespace Twil {
namespace Ui {

WindowControl::WindowControl() :
	mNeedsRedraw{false}
{}

void WindowControl::setNeedsRedraw(bool NeedsRedraw)
{
	mNeedsRedraw = NeedsRedraw;
}

bool WindowControl::getNeedsRedraw() {
	return mNeedsRedraw;
}

}
}
