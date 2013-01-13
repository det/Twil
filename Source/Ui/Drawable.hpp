#pragma once

#include "Ui/Resizable.hpp"

namespace Twil {

namespace Ui {

template<bool W, bool V>
class Drawable :
	Ui::Resizable<W, V>
{
	public:
	virtual ~Drawable() {}

	virtual void setX(signed short) = 0;
	virtual void setY(signed short) = 0;
	virtual void setClipX(signed short, signed short) = 0;
	virtual void setClipY(signed short, signed short) = 0;

	virtual unsigned short getX() = 0;
	virtual unsigned short getY() = 0;
	virtual unsigned short getWidth() = 0;
	virtual unsigned short getHeight() = 0;
	virtual unsigned short getFitWidth() = 0;
	virtual unsigned short getFitHeight() = 0;

	virtual void draw() = 0;
};

}
}
