#include "Theme/Button.hpp"

#include "Theme/Manager.hpp"

namespace Twil {
namespace Theme {

Button::Button(Theme::Manager & Manager) :
	mManager{Manager},
	mVertices{9}
{
	Attribute::Color4b BorderColor{127, 127, 127, 255};

	mVertices[0].BorderColor = BorderColor;
	mVertices[1].BorderColor = BorderColor;
	mVertices[2].BorderColor = BorderColor;
	mVertices[3].BorderColor = BorderColor;
	mVertices[4].BorderColor = BorderColor;
	mVertices[5].BorderColor = BorderColor;
	mVertices[6].BorderColor = BorderColor;
	mVertices[7].BorderColor = BorderColor;
	mVertices[8].BorderColor = BorderColor;
}

void Button::setIsDown(bool IsPressed)
{
	mIsDown = IsPressed;

	Attribute::Color4b Color1;
	Attribute::Color4b Color2;

	if (IsPressed) {
		Color1 =  {191, 191, 191, 255};
		Color2 = {111, 111, 111, 255};
	}
	else {
		Color1 =  {255, 255, 255, 255};
		Color2 = {159, 159, 159, 255};
	}

	Attribute::Color4b TopColor1 = mix(Color2, Color1, mHeight, mHeight - 1);
	Attribute::Color4b TopColor2 = mix(Color2, Color1, mHeight, mHeight - 4);
	Attribute::Color4b BottomColor2 = mix(Color2, Color1, mHeight, 4);
	Attribute::Color4b BottomColor1 = mix(Color2, Color1, mHeight, 1);

	mVertices[0].TopColor = BottomColor2;
	mVertices[0].BottomColor = BottomColor1;
	mVertices[1].TopColor = BottomColor2;
	mVertices[1].BottomColor = BottomColor1;
	mVertices[2].TopColor = TopColor1;
	mVertices[2].BottomColor = TopColor2;
	mVertices[3].TopColor = TopColor1;
	mVertices[3].BottomColor = TopColor2;
	mVertices[4].TopColor = BottomColor2;
	mVertices[4].BottomColor = BottomColor1;
	mVertices[5].TopColor = TopColor1;
	mVertices[5].BottomColor = TopColor2;
	mVertices[6].TopColor = TopColor2;
	mVertices[6].BottomColor = BottomColor2;
	mVertices[7].TopColor = TopColor2;
	mVertices[7].BottomColor = BottomColor2;
	mVertices[8].TopColor = TopColor2;
	mVertices[8].BottomColor = BottomColor2;
}

void Button::resize(unsigned short Width, unsigned short Height)
{
	mWidth = Width;
	mHeight = Height;

	GLshort MiddleX = mX + 5;
	GLshort MiddleY = mY + 5;
	GLshort Left = mX + 0;
	GLshort Right = mX + Width - 5;
	GLshort Bottom = mY + 0;
	GLshort Top = mY + Height - 5;
	GLushort ScaleX = Width - 10;
	GLushort ScaleY = Height - 10;

	mVertices[0].InsideOffset = {mManager.mButtonSwInside};
	mVertices[0].OutsideOffset = {mManager.mButtonSwOutside};
	mVertices[0].Position = {Left, Bottom};
	mVertices[0].Size = {5, 5};
	mVertices[0].Scale = {1, 1};

	mVertices[1].InsideOffset = {mManager.mButtonSeInside};
	mVertices[1].OutsideOffset = {mManager.mButtonSeOutside};
	mVertices[1].Position = {Right, Bottom};
	mVertices[1].Size = {5, 5};
	mVertices[1].Scale = {1, 1};

	mVertices[2].InsideOffset = {mManager.mButtonNeInside};
	mVertices[2].OutsideOffset = {mManager.mButtonNeOutside};
	mVertices[2].Position = {Right, Top};
	mVertices[2].Size = {5, 5};
	mVertices[2].Scale = {1, 1};

	mVertices[3].InsideOffset = {mManager.mButtonNwInside};
	mVertices[3].OutsideOffset = {mManager.mButtonNwOutside};
	mVertices[3].Position = {Left, Top};
	mVertices[3].Size = {5, 5};
	mVertices[3].Scale = {1, 1};

	mVertices[4].InsideOffset = {mManager.mButtonBottomInside};
	mVertices[4].OutsideOffset = {mManager.mButtonBottomOutside};
	mVertices[4].Position = {MiddleX, Bottom};
	mVertices[4].Size = {1, 5};
	mVertices[4].Scale = {ScaleX, 1};

	mVertices[5].InsideOffset = {mManager.mButtonTopInside};
	mVertices[5].OutsideOffset = {mManager.mButtonTopOutside};
	mVertices[5].Position = {MiddleX, Top};
	mVertices[5].Size = {1, 5};
	mVertices[5].Scale = {ScaleX, 1};

	mVertices[6].InsideOffset = {mManager.mButtonLeftInside};
	mVertices[6].OutsideOffset = {mManager.mButtonLeftOutside};
	mVertices[6].Position = {Left, MiddleY};
	mVertices[6].Size = {5, 1};
	mVertices[6].Scale = {1, ScaleY};

	mVertices[7].InsideOffset = {mManager.mButtonRightInside};
	mVertices[7].OutsideOffset = {mManager.mButtonRightOutside};
	mVertices[7].Position = {Right, MiddleY};
	mVertices[7].Size = {5, 1};
	mVertices[7].Scale = {1, ScaleY};

	mVertices[8].InsideOffset = {mManager.mButtonCenterInside};
	mVertices[8].OutsideOffset = {mManager.mButtonCenterOutside};
	mVertices[8].Position = {MiddleX, MiddleY};
	mVertices[8].Size = {1, 1};
	mVertices[8].Scale = {ScaleX, ScaleY};

	setIsDown(mIsDown);
}

void Button::move(signed short X, signed short Y)
{
	auto DeltaX = X - mX;
	auto DeltaY = Y - mY;

	for (auto & Vertex : mVertices) {
		Vertex.Position.X += DeltaX;
		Vertex.Position.Y += DeltaY;
	}

	mX = X;
	mY = Y;
}

void Button::render()
{
	mManager.mOutlineArray.add(mVertices);
}

signed short Button::getChildX()
{
	return mX + 2;
}

signed short Button::getChildY()
{
	return mY + 2;
}

unsigned short Button::getChildWidth()
{
	return mWidth - 4;
}

unsigned short Button::getChildHeight()
{
	return mHeight - 4;
}

unsigned short Button::getFitWidth(unsigned short Width)
{
	return Width + 12;
}

unsigned short Button::getFitHeight(unsigned short Height)
{
	return Height + 12;
}

signed short Button::getX()
{
	return mX;
}

signed short Button::getY()
{
	return mY;
}

unsigned short Button::getWidth()
{
	return mWidth;
}

unsigned short Button::getHeight()
{
	return mHeight;
}

}
}
