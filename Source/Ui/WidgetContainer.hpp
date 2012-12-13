#pragma once

#include "Ui/DrawableContainer.hpp"

namespace Twil {
namespace Ui {

class WidgetContainer :
	public DrawableContainer
{
	public:
	virtual ~WidgetContainer() {}
	virtual void releaseMouse(signed short, signed short) = 0;
};

}
}
