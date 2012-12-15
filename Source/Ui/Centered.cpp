#include "Ui/Centered.hpp"

namespace Twil {
namespace Ui {

void Centered::resize(unsigned short Width, unsigned short Height)
{
	mWidth = Width;
	mHeight = Height;
}

void Centered::move(signed short X, signed short Y)
{
	mX = X;
	mY = Y;
}

unsigned short Centered::getLayoutX(unsigned short Width)
{
	return mX + (mWidth - Width) / 2;
}

unsigned short Centered::getLayoutY(unsigned short Height)
{
	return mY + (mHeight - Height) / 2;
}

}
}
