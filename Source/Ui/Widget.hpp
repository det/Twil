#pragma once

#include "Ui/Drawable.hpp"

namespace Twil {
namespace Ui {

template<bool W, bool V>
class Widget :
	public Ui::Drawable<W, V>
{
	public:
	virtual ~Widget() {}
	virtual void aquireMouse(signed short, signed short) = 0;
};

}
}
