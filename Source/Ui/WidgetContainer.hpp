#pragma once

#include "Ui/DrawableContainer.hpp"

namespace Twil {
namespace Ui {

template<bool, bool>
class WidgetContainer;

template<>
class WidgetContainer<true, true> :
	public DrawableContainer<true, true>
{
	public:
	virtual ~WidgetContainer() {}
	virtual void releaseMouse(signed short, signed short) = 0;
};

}
}
