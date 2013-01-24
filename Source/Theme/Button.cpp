#include "Button.hpp"

#include "Manager.hpp"

#include <iostream>

namespace Twil {
namespace Theme {

namespace {

template<typename T>
void clipVertexLeft(T & Vertex, signed short X)
{
	Vertex.ClipMin.X = X;
	Vertex.ClipMin.X = std::max<signed short>(Vertex.ClipMin.X, Vertex.PositionMin.X);
	Vertex.ClipMin.X = std::min<signed short>(Vertex.ClipMin.X, Vertex.PositionMax.X);
}

template<typename T>
void clipVertexRight(T & Vertex, signed short X)
{
	Vertex.ClipMax.X = X;
	Vertex.ClipMax.X = std::max<signed short>(Vertex.ClipMax.X, Vertex.PositionMin.X);
	Vertex.ClipMax.X = std::min<signed short>(Vertex.ClipMax.X, Vertex.PositionMax.X);
}

template<typename T>
void clipVertexBottom(T & Vertex, signed short Y)
{
	Vertex.ClipMin.Y = Y;
	Vertex.ClipMin.Y = std::max<signed short>(Vertex.ClipMin.Y, Vertex.PositionMin.Y);
	Vertex.ClipMin.Y = std::min<signed short>(Vertex.ClipMin.Y, Vertex.PositionMax.Y);
}

template<typename T>
void clipVertexTop(T & Vertex, signed short Y)
{
	Vertex.ClipMax.Y = Y;
	Vertex.ClipMax.Y = std::max<signed short>(Vertex.ClipMax.Y, Vertex.PositionMin.Y);
	Vertex.ClipMax.Y = std::min<signed short>(Vertex.ClipMax.Y, Vertex.PositionMax.Y);
}

}

ButtonT::ButtonT(ManagerT & Manager) :
	mManager(Manager), // Gcc bug prevents brace initialization syntax here
	mVertices{9}
{
	signed short const BorderSize = 1;
	signed short const CornerSize = BorderSize + Settings::Button::Roundness;

	mVertices[0].BorderColor = Settings::Button::BorderColor;
	mVertices[0].BottomColor = {255, 0, 0, 127};
	mVertices[0].TopColor = {255, 0, 0, 127};
	mVertices[0].ClipMin = {0, 0};
	mVertices[0].ClipMax = {0, 0};
	mVertices[0].PositionMin = {0, 0};
	mVertices[0].PositionMax = {CornerSize, CornerSize};
	mVertices[0].TextureSize = {CornerSize, CornerSize};
	mVertices[0].InsideIndex = {mManager.mButtonSwInside};
	mVertices[0].OutsideIndex = {mManager.mButtonSwOutside};
	mVertices[1].BorderColor = Settings::Button::BorderColor;
	mVertices[1].BottomColor = {255, 0, 0, 127};
	mVertices[1].TopColor = {255, 0, 0, 127};
	mVertices[1].ClipMin = {-CornerSize, 0};
	mVertices[1].ClipMax = {-CornerSize, 0};
	mVertices[1].PositionMin = {-CornerSize, 0};
	mVertices[1].PositionMax = {0, CornerSize};
	mVertices[1].TextureSize = {CornerSize, CornerSize};
	mVertices[1].InsideIndex = {mManager.mButtonSeInside};
	mVertices[1].OutsideIndex = {mManager.mButtonSeOutside};
	mVertices[2].BorderColor = Settings::Button::BorderColor;
	mVertices[2].BottomColor = {255, 0, 0, 127};
	mVertices[2].TopColor = {255, 0, 0, 127};
	mVertices[2].ClipMin = {-CornerSize, -CornerSize};
	mVertices[2].ClipMax = {-CornerSize, -CornerSize};
	mVertices[2].PositionMin = {-CornerSize, -CornerSize};
	mVertices[2].PositionMax = {0, 0};
	mVertices[2].TextureSize = {CornerSize, CornerSize};
	mVertices[2].InsideIndex = {mManager.mButtonNeInside};
	mVertices[2].OutsideIndex = {mManager.mButtonNeOutside};
	mVertices[3].BorderColor = Settings::Button::BorderColor;
	mVertices[3].BottomColor = {255, 0, 0, 127};
	mVertices[3].TopColor = {255, 0, 0, 127};
	mVertices[3].ClipMin = {0, -CornerSize};
	mVertices[3].ClipMax = {0, -CornerSize};
	mVertices[3].PositionMin = {0, -CornerSize};
	mVertices[3].PositionMax = {CornerSize, 0};
	mVertices[3].TextureSize = {CornerSize, CornerSize};
	mVertices[3].InsideIndex = {mManager.mButtonNwInside};
	mVertices[3].OutsideIndex = {mManager.mButtonNwOutside};
	mVertices[4].BorderColor = Settings::Button::BorderColor;
	mVertices[4].BottomColor = {0, 255, 0, 127};
	mVertices[4].TopColor = {0, 255, 0, 127};
	mVertices[4].ClipMin = {CornerSize, 0};
	mVertices[4].ClipMax = {CornerSize, 0};
	mVertices[4].PositionMin = {CornerSize, 0};
	mVertices[4].PositionMax = {-CornerSize, CornerSize};
	mVertices[4].TextureSize = {BorderSize, CornerSize};
	mVertices[4].InsideIndex = {mManager.mButtonBottomInside};
	mVertices[4].OutsideIndex = {mManager.mButtonBottomOutside};
	mVertices[5].BorderColor = Settings::Button::BorderColor;
	mVertices[5].BottomColor = {0, 255, 0, 127};
	mVertices[5].TopColor = {0, 255, 0, 127};
	mVertices[5].ClipMin = {CornerSize, -CornerSize};
	mVertices[5].ClipMax = {CornerSize, -CornerSize};
	mVertices[5].PositionMin = {CornerSize, -CornerSize};
	mVertices[5].PositionMax = {-CornerSize, 0};
	mVertices[5].TextureSize = {BorderSize, CornerSize};
	mVertices[5].InsideIndex = {mManager.mButtonTopInside};
	mVertices[5].OutsideIndex = {mManager.mButtonTopOutside};
	mVertices[6].BorderColor = Settings::Button::BorderColor;
	mVertices[6].BottomColor = {0, 255, 0, 127};
	mVertices[6].TopColor = {0, 255, 0, 127};
	mVertices[6].ClipMin = {0, CornerSize};
	mVertices[6].ClipMax = {0, CornerSize};
	mVertices[6].PositionMin = {0, CornerSize};
	mVertices[6].PositionMax = {CornerSize, -CornerSize};
	mVertices[6].TextureSize = {CornerSize, BorderSize};
	mVertices[6].InsideIndex = {mManager.mButtonLeftInside};
	mVertices[6].OutsideIndex = {mManager.mButtonLeftOutside};
	mVertices[7].BorderColor = Settings::Button::BorderColor;
	mVertices[7].BottomColor = {0, 255, 0, 127};
	mVertices[7].TopColor = {0, 255, 0, 127};
	mVertices[7].ClipMin = {-CornerSize, CornerSize};
	mVertices[7].ClipMax = {-CornerSize, CornerSize};
	mVertices[7].PositionMin = {-CornerSize, CornerSize};
	mVertices[7].PositionMax = {0, -CornerSize};
	mVertices[7].TextureSize = {CornerSize, BorderSize};
	mVertices[7].InsideIndex = {mManager.mButtonRightInside};
	mVertices[7].OutsideIndex = {mManager.mButtonRightOutside};
	mVertices[8].BorderColor = Settings::Button::BorderColor;
	mVertices[8].BottomColor = {0, 0, 255, 127};
	mVertices[8].TopColor = {0, 0, 255, 127};
	mVertices[8].ClipMin = {CornerSize, CornerSize};
	mVertices[8].ClipMax = {CornerSize, CornerSize};
	mVertices[8].PositionMin = {CornerSize, CornerSize};
	mVertices[8].PositionMax = {-CornerSize, -CornerSize};
	mVertices[8].TextureSize = {BorderSize, BorderSize};
	mVertices[8].InsideIndex = {mManager.mButtonCenterInside};
	mVertices[8].OutsideIndex = {mManager.mButtonCenterOutside};
}

void ButtonT::setIsDown(bool IsDown)
{
	//return;
	mIsDown = IsDown;
	if (mLeft == mRight || mBottom == mTop) return;

	Attribute::Color4bT Color1;
	Attribute::Color4bT Color2;

	if (IsDown) {
		Color1 = Settings::Button::TopDownColor;
		Color2 = Settings::Button::BottomDownColor;
	}
	else {
		Color1 = Settings::Button::TopUpColor;
		Color2 = Settings::Button::BottomUpColor;
	}

	signed short Height = mTop - mBottom;
	for (auto & Vertex : mVertices) {
		Vertex.BottomColor = mix(Color1, Color2, (Vertex.ClipMin.Y - mBottom) * 65535 / Height);
		Vertex.TopColor = mix(Color1, Color2, (Vertex.ClipMax.Y - mBottom) * 65535 / Height);
	}
}

signed short ButtonT::getLeftMargin() const
{
	return 3;
}

signed short ButtonT::getBottomMargin() const
{
	return 3;
}

signed short ButtonT::getRightMargin() const
{
	return 3;
}

signed short ButtonT::getTopMargin() const
{
	return 3;
}

void ButtonT::moveX(signed short X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;

	for (auto & Vertex : mVertices)	{
		Vertex.ClipMin.X += X;
		Vertex.ClipMax.X += X;
		Vertex.PositionMin.X += X;
		Vertex.PositionMax.X += X;
	}
}

void ButtonT::moveY(signed short Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;

	for (auto & Vertex : mVertices) {
		Vertex.ClipMin.Y += Y;
		Vertex.ClipMax.Y += Y;
		Vertex.PositionMin.Y += Y;
		Vertex.PositionMax.Y += Y;
	}
}

void ButtonT::resizeWidth(signed short X)
{
	mRight += X;
	mClipRight += X;

	signed short const BorderSize = 1;
	signed short const CornerSize = BorderSize + Settings::Button::Roundness;

	signed short FirstMax = mLeft + CornerSize;
	signed short SecondMin = FirstMax;
	signed short SecondMax = mRight - CornerSize;
	signed short ThirdMin = SecondMax;
	signed short ThirdMax = mRight;

	SecondMax = std::max(SecondMin, SecondMax);

	mVertices[1].PositionMin.X = ThirdMin;
	mVertices[1].PositionMax.X = ThirdMax;
	mVertices[2].PositionMin.X = ThirdMin;
	mVertices[2].PositionMax.X = ThirdMax;
	mVertices[4].PositionMax.X = SecondMax;
	mVertices[5].PositionMax.X = SecondMax;
	mVertices[7].PositionMin.X = ThirdMin;
	mVertices[7].PositionMax.X = ThirdMax;
	mVertices[8].PositionMax.X = SecondMax;

	clipLeftCenter();
	clipRightCenter();
	clipRight();
}

void ButtonT::resizeHeight(signed short Y)
{
	mTop += Y;
	mClipTop += Y;

	signed short const BorderSize = 1;
	signed short const CornerSize = BorderSize + Settings::Button::Roundness;

	signed short FirstMax = mBottom + CornerSize;
	signed short SecondMin = FirstMax;
	signed short SecondMax = mTop - CornerSize;
	signed short ThirdMin = SecondMax;
	signed short ThirdMax = mTop;

	SecondMax = std::max(SecondMin, SecondMax);

	mVertices[2].PositionMin.Y = ThirdMin;
	mVertices[2].PositionMax.Y = ThirdMax;
	mVertices[3].PositionMin.Y = ThirdMin;
	mVertices[3].PositionMax.Y = ThirdMax;
	mVertices[5].PositionMin.Y = ThirdMin;
	mVertices[5].PositionMax.Y = ThirdMax;
	mVertices[6].PositionMax.Y = SecondMax;
	mVertices[7].PositionMax.Y = SecondMax;
	mVertices[8].PositionMax.Y = SecondMax;

	clipBottomCenter();
	clipTopCenter();
	clipTop();
	setIsDown(mIsDown);
}

void ButtonT::clipLeft()
{
	clipVertexLeft(mVertices[0], mClipLeft);
	clipVertexLeft(mVertices[3], mClipLeft);
	clipVertexLeft(mVertices[4], mClipLeft);
	clipVertexLeft(mVertices[5], mClipLeft);
	clipVertexLeft(mVertices[6], mClipLeft);
	clipVertexLeft(mVertices[8], mClipLeft);
}

void ButtonT::clipLeftCenter()
{
	signed short Center = (mRight + mLeft) / 2;
	signed short CenterClip = std::max(Center, mClipLeft);

	clipVertexLeft(mVertices[1], CenterClip);
	clipVertexLeft(mVertices[2], CenterClip);
	clipVertexLeft(mVertices[7], CenterClip);
}

void ButtonT::setClipLeft(signed short X)
{
	mClipLeft = X;
	clipLeft();
	clipLeftCenter();

}

void ButtonT::clipBottom()
{
	clipVertexBottom(mVertices[0], mClipBottom);
	clipVertexBottom(mVertices[1], mClipBottom);
	clipVertexBottom(mVertices[4], mClipBottom);
	clipVertexBottom(mVertices[6], mClipBottom);
	clipVertexBottom(mVertices[7], mClipBottom);
	clipVertexBottom(mVertices[8], mClipBottom);
}

void ButtonT::clipBottomCenter()
{
	signed short Center = (mBottom + mTop) / 2;
	signed short CenterClip = std::max(Center, mClipBottom);

	clipVertexBottom(mVertices[2], CenterClip);
	clipVertexBottom(mVertices[3], CenterClip);
	clipVertexBottom(mVertices[5], CenterClip);
}

void ButtonT::setClipBottom(signed short Y)
{
	mClipBottom = Y;
	clipBottom();
	clipBottomCenter();
	setIsDown(mIsDown);
}

void ButtonT::clipRight()
{
	clipVertexRight(mVertices[1], mClipRight);
	clipVertexRight(mVertices[2], mClipRight);
	clipVertexRight(mVertices[4], mClipRight);
	clipVertexRight(mVertices[5], mClipRight);
	clipVertexRight(mVertices[7], mClipRight);
	clipVertexRight(mVertices[8], mClipRight);
}

void ButtonT::clipRightCenter()
{
	signed short Center = (mRight + mLeft) / 2;
	signed short CenterClip = std::min(Center, mClipRight);

	clipVertexRight(mVertices[0], CenterClip);
	clipVertexRight(mVertices[3], CenterClip);
	clipVertexRight(mVertices[6], CenterClip);
}

void ButtonT::setClipRight(signed short X)
{
	mClipRight = X;
	clipRight();
	clipRightCenter();
}

void ButtonT::clipTop()
{
	clipVertexTop(mVertices[2], mClipTop);
	clipVertexTop(mVertices[3], mClipTop);
	clipVertexTop(mVertices[5], mClipTop);
	clipVertexTop(mVertices[6], mClipTop);
	clipVertexTop(mVertices[7], mClipTop);
	clipVertexTop(mVertices[8], mClipTop);
}

void ButtonT::clipTopCenter()
{
	signed short Center = (mBottom + mTop) / 2;
	signed short CenterClip = std::min(Center, mClipTop);

	clipVertexTop(mVertices[0], CenterClip);
	clipVertexTop(mVertices[1], CenterClip);
	clipVertexTop(mVertices[4], CenterClip);
}

void ButtonT::setClipTop(signed short Y)
{
	mClipTop = Y;
	clipTop();
	clipTopCenter();
	setIsDown(mIsDown);
}

void ButtonT::draw() const
{
	if (mClipLeft > mClipRight || mClipBottom > mClipTop) return;
	mManager.mOutlineArray.queue(mVertices);
}

signed short ButtonT::getLeft() const
{
	return mLeft;
}

signed short ButtonT::getBottom() const
{
	return mBottom;
}

signed short ButtonT::getRight() const
{
	return mRight;
}

signed short ButtonT::getTop() const
{
	return mTop;
}

signed short ButtonT::getBaseWidth(signed short Width) const
{
	return Width + 12;
}

signed short ButtonT::getBaseHeight(signed short Height) const
{
	return Height + 12;
}

}
}
