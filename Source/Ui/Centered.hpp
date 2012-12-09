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
	unsigned short getX(unsigned short);
	unsigned short getY(unsigned short);
};

}
}
