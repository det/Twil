#pragma once

namespace Twil {

namespace Ui {

class Drawable
{
	public:
	virtual ~Drawable() {}
	virtual void handleResized(unsigned short, unsigned short) = 0;
	virtual void handleMoved(short, short) = 0;
	virtual unsigned short getFitWidth() = 0;
	virtual unsigned short getFitHeight() = 0;
	virtual unsigned short getWidth() = 0;
	virtual unsigned short getHeight() = 0;
	virtual unsigned short getX() = 0;
	virtual unsigned short getY() = 0;
	virtual void draw() = 0;
};

}
}
