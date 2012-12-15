#pragma once

namespace Twil {
namespace Ui {

class Centered
{
	private:
	unsigned short mX = 0;
	unsigned short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	void resize(unsigned short, unsigned short);
	void move(signed short, signed short);
	unsigned short getLayoutX(unsigned short);
	unsigned short getLayoutY(unsigned short);

	unsigned short getWidth() { return mWidth; }
	unsigned short getHeight() { return mHeight; }
	unsigned short getX() { return mX; }
	unsigned short getY() { return mY; }

};

}
}
