#pragma once

#include "Ui/Drawable.hpp"

namespace Twil {
namespace Ui {

class Widget :
	public Ui::Drawable
{
	public:
	virtual ~Widget() {}
	virtual void aquireMouse(signed short, signed short) = 0;
};

}
}
