#include "Button.hpp"

namespace Twil {
namespace Theme {

void ButtonT::init(ManagerT & Manager)
{
	mManager = &Manager;
	mManager->mOutlineArray.allocate(*this, 9);
}

void ButtonT::setIsDown(bool IsDown)
{
	mIsDown = IsDown;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

std::int16_t ButtonT::getLeftMargin() const
{
	return Settings::Button::LeftMargin;
}

std::int16_t ButtonT::getRightMargin() const
{
	return Settings::Button::RightMargin;
}

std::int16_t ButtonT::getBottomMargin() const
{
	return Settings::Button::BottomMargin;
}

std::int16_t ButtonT::getTopMargin() const
{
	return Settings::Button::TopMargin;
}

void ButtonT::moveX(std::int16_t X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::moveY(std::int16_t Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::resizeWidth(std::int16_t X)
{
	mRight += X;
	mClipRight += X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::resizeHeight(std::int16_t Y)
{
	mTop += Y;
	mClipTop += Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipLeft(std::int16_t X)
{
	mClipLeft = X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipRight(std::int16_t X)
{
	mClipRight = X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipBottom(std::int16_t Y)
{
	mClipBottom = Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipTop(std::int16_t Y)
{
	mClipTop = Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::draw(Vertex::OutlineGradientT * Vertices) const
{
	std::int16_t Left = mLeft;
	std::int16_t MiddleLeft = mLeft + mCornerSize;
	std::int16_t MiddleRight = mRight - mCornerSize;
	std::int16_t Right = mRight;

	std::int16_t Bottom = mBottom;
	std::int16_t MiddleBottom = mBottom + mCornerSize;
	std::int16_t MiddleTop = mTop - mCornerSize;
	std::int16_t Top = mTop;

	std::int16_t ClipLeft = Left;
	std::int16_t ClipMiddleLeft = MiddleLeft;
	std::int16_t ClipMiddleRight = MiddleRight;
	std::int16_t ClipRight = Right;

	std::int16_t ClipBottom = Bottom;
	std::int16_t ClipMiddleBottom = MiddleBottom;
	std::int16_t ClipMiddleTop = MiddleTop;
	std::int16_t ClipTop = Top;

	std::int16_t Height = Top - Bottom;
	std::int16_t CenterX = (Left + Right) / 2;
	std::int16_t CenterY = (Bottom + Top) / 2;

	ClipMiddleLeft = std::min<std::int16_t>(ClipMiddleLeft, CenterX);
	ClipMiddleRight = std::max<std::int16_t>(ClipMiddleRight, CenterX);
	ClipMiddleBottom = std::min<std::int16_t>(ClipMiddleBottom, CenterY);
	ClipMiddleTop = std::max<std::int16_t>(ClipMiddleTop, CenterY);

	ClipLeft = std::max<std::int16_t>(ClipLeft, mClipLeft);
	ClipMiddleLeft = std::max<std::int16_t>(ClipMiddleLeft, mClipLeft);
	ClipMiddleRight = std::max<std::int16_t>(ClipMiddleRight, mClipLeft);
	ClipRight = std::max<std::int16_t>(ClipRight, mClipLeft);

	ClipLeft = std::min<std::int16_t>(ClipLeft, mClipRight);
	ClipMiddleLeft = std::min<std::int16_t>(ClipMiddleLeft, mClipRight);
	ClipMiddleRight = std::min<std::int16_t>(ClipMiddleRight, mClipRight);
	ClipRight = std::min<std::int16_t>(ClipRight, mClipRight);

	ClipBottom = std::min<std::int16_t>(ClipBottom, mClipTop);
	ClipMiddleBottom = std::min<std::int16_t>(ClipMiddleBottom, mClipTop);
	ClipMiddleTop = std::min<std::int16_t>(ClipMiddleTop, mClipTop);
	ClipTop = std::min<std::int16_t>(ClipTop, mClipTop);

	ClipBottom = std::max<std::int16_t>(ClipBottom, mClipBottom);
	ClipMiddleBottom = std::max<std::int16_t>(ClipMiddleBottom, mClipBottom);
	ClipMiddleTop = std::max<std::int16_t>(ClipMiddleTop, mClipBottom);
	ClipTop = std::max<std::int16_t>(ClipTop, mClipBottom);

	Attribute::Color4bT TopColor;
	Attribute::Color4bT MiddleBottomColor;
	Attribute::Color4bT MiddleTopColor;
	Attribute::Color4bT BottomColor;

	// Avoid divide by 0, the colors dont matter for 0 size rectangles
	if (Height != 0)
	{
		if (mIsDown)
		{
			TopColor = Settings::Button::TopDownColor;
			BottomColor = Settings::Button::BottomDownColor;
		}
		else
		{
			TopColor = Settings::Button::TopUpColor;
			BottomColor = Settings::Button::BottomUpColor;
		}

		MiddleBottomColor =	mix(
			TopColor,
			BottomColor,
			(ClipMiddleBottom - Bottom) * 65535 / Height);

		MiddleTopColor = mix(
			TopColor,
			BottomColor,
			(ClipMiddleTop - Bottom) * 65535 / Height);
	}

	Vertices[0].BorderColor = Settings::Button::BorderColor;
	Vertices[0].BottomColor = BottomColor;
	Vertices[0].TopColor = MiddleBottomColor;
	Vertices[0].ClipMin.S = (ClipLeft - Left) * 65535 / mCornerSize;
	Vertices[0].ClipMin.T = (ClipBottom - Bottom) * 65535 / mCornerSize;
	Vertices[0].ClipMax.S = (ClipMiddleLeft - Left) * 65535 / mCornerSize;
	Vertices[0].ClipMax.T = (ClipMiddleBottom - Bottom) * 65535 / mCornerSize;
	Vertices[0].PositionMin = {ClipLeft, ClipBottom};
	Vertices[0].PositionMax = {ClipMiddleLeft, ClipMiddleBottom};
	Vertices[0].TextureSize = {mCornerSize, mCornerSize};
	Vertices[0].InIndex = {mManager->mButtonSwIn};
	Vertices[0].OutIndex = {mManager->mButtonSwOut};

	Vertices[1].BorderColor = Settings::Button::BorderColor;
	Vertices[1].BottomColor = BottomColor;
	Vertices[1].TopColor = MiddleBottomColor;
	Vertices[1].ClipMin.S = (ClipMiddleRight - MiddleRight) * 65535 / mCornerSize;
	Vertices[1].ClipMin.T = (ClipBottom - Bottom) * 65535 / mCornerSize;
	Vertices[1].ClipMax.S = (ClipRight - MiddleRight) * 65535 / mCornerSize;
	Vertices[1].ClipMax.T = (ClipMiddleBottom - Bottom) * 65535 / mCornerSize;
	Vertices[1].PositionMin = {ClipMiddleRight, ClipBottom};
	Vertices[1].PositionMax = {ClipRight, ClipMiddleBottom};
	Vertices[1].TextureSize = {mCornerSize, mCornerSize};
	Vertices[1].InIndex = {mManager->mButtonSeIn};
	Vertices[1].OutIndex = {mManager->mButtonSeOut};

	Vertices[2].BorderColor = Settings::Button::BorderColor;
	Vertices[2].BottomColor = MiddleTopColor;
	Vertices[2].TopColor = TopColor;
	Vertices[2].ClipMin.S = (ClipMiddleRight - MiddleRight) * 65535 / mCornerSize;
	Vertices[2].ClipMin.T = (ClipMiddleTop - MiddleTop) * 65535 / mCornerSize;
	Vertices[2].ClipMax.S = (ClipRight - MiddleRight) * 65535 / mCornerSize;
	Vertices[2].ClipMax.T = (ClipTop - MiddleTop) * 65535 / mCornerSize;
	Vertices[2].PositionMin = {ClipMiddleRight, ClipMiddleTop};
	Vertices[2].PositionMax = {ClipRight, ClipTop};
	Vertices[2].TextureSize = {mCornerSize, mCornerSize};
	Vertices[2].InIndex = {mManager->mButtonNeIn};
	Vertices[2].OutIndex = {mManager->mButtonNeOut};

	Vertices[3].BorderColor = Settings::Button::BorderColor;
	Vertices[3].BottomColor = MiddleTopColor;
	Vertices[3].TopColor = TopColor;
	Vertices[3].ClipMin.S = (ClipLeft - Left) * 65535 / mCornerSize;
	Vertices[3].ClipMin.T = (ClipMiddleTop - MiddleTop) * 65535 / mCornerSize;
	Vertices[3].ClipMax.S = (ClipMiddleLeft - Left) * 65535 / mCornerSize;
	Vertices[3].ClipMax.T = (ClipTop - MiddleTop) * 65535 / mCornerSize;
	Vertices[3].PositionMin = {ClipLeft, ClipMiddleTop};
	Vertices[3].PositionMax = {ClipMiddleLeft, ClipTop};
	Vertices[3].TextureSize = {mCornerSize, mCornerSize};
	Vertices[3].InIndex = {mManager->mButtonNwIn};
	Vertices[3].OutIndex = {mManager->mButtonNwOut};

	Vertices[4].BorderColor = Settings::Button::BorderColor;
	Vertices[4].BottomColor = BottomColor;
	Vertices[4].TopColor = MiddleBottomColor;
	Vertices[4].ClipMin.S = 0;
	Vertices[4].ClipMin.T = (ClipBottom - Bottom) * 65535 / mCornerSize;
	Vertices[4].ClipMax.S = 65535;
	Vertices[4].ClipMax.T = (ClipMiddleBottom - Bottom) * 65535 / mCornerSize;
	Vertices[4].PositionMin = {ClipMiddleLeft, ClipBottom};
	Vertices[4].PositionMax = {ClipMiddleRight, ClipMiddleBottom};
	Vertices[4].TextureSize = {mBorderSize, mCornerSize};
	Vertices[4].InIndex = {mManager->mButtonBottomIn};
	Vertices[4].OutIndex = {mManager->mButtonBottomOut};

	Vertices[5].BorderColor = Settings::Button::BorderColor;
	Vertices[5].BottomColor = MiddleTopColor;
	Vertices[5].TopColor = TopColor;
	Vertices[5].ClipMin.S = 0;
	Vertices[5].ClipMin.T = (ClipMiddleTop - MiddleTop) * 65535 / mCornerSize;
	Vertices[5].ClipMax.S = 65535;
	Vertices[5].ClipMax.T = (ClipTop - MiddleTop) * 65535 / mCornerSize;
	Vertices[5].PositionMin = {ClipMiddleLeft, ClipMiddleTop};
	Vertices[5].PositionMax = {ClipMiddleRight, ClipTop};
	Vertices[5].TextureSize = {mBorderSize, mCornerSize};
	Vertices[5].InIndex = {mManager->mButtonTopIn};
	Vertices[5].OutIndex = {mManager->mButtonTopOut};

	Vertices[6].BorderColor = Settings::Button::BorderColor;
	Vertices[6].BottomColor = MiddleBottomColor;
	Vertices[6].TopColor = MiddleTopColor;
	Vertices[6].ClipMin.S = (ClipLeft - Left) * 65535 / mCornerSize;
	Vertices[6].ClipMin.T = 0;
	Vertices[6].ClipMax.S = (ClipMiddleLeft - Left) * 65535 / mCornerSize;
	Vertices[6].ClipMax.T = 65535;
	Vertices[6].PositionMin = {ClipLeft, ClipMiddleBottom};
	Vertices[6].PositionMax = {ClipMiddleLeft, ClipMiddleTop};
	Vertices[6].TextureSize = {mCornerSize, mBorderSize};
	Vertices[6].InIndex = {mManager->mButtonLeftIn};
	Vertices[6].OutIndex = {mManager->mButtonLeftOut};

	Vertices[7].BorderColor = Settings::Button::BorderColor;
	Vertices[7].BottomColor = MiddleBottomColor;
	Vertices[7].TopColor = MiddleTopColor;
	Vertices[7].ClipMin.S = (ClipMiddleRight - MiddleRight) * 65535 / mCornerSize;
	Vertices[7].ClipMin.T = 0;
	Vertices[7].ClipMax.S = (ClipRight - MiddleRight) * 65535 / mCornerSize;
	Vertices[7].ClipMax.T = 65535;
	Vertices[7].PositionMin = {ClipMiddleRight, ClipMiddleBottom};
	Vertices[7].PositionMax = {ClipRight, ClipMiddleTop};
	Vertices[7].TextureSize = {mCornerSize, mBorderSize};
	Vertices[7].InIndex = {mManager->mButtonRightIn};
	Vertices[7].OutIndex = {mManager->mButtonRightOut};

	Vertices[8].BorderColor = Settings::Button::BorderColor;
	Vertices[8].BottomColor = MiddleBottomColor;
	Vertices[8].TopColor = MiddleTopColor;
	Vertices[8].ClipMin = {0, 0};
	Vertices[8].ClipMax = {65535, 65535};
	Vertices[8].PositionMin = {ClipMiddleLeft, ClipMiddleBottom};
	Vertices[8].PositionMax = {ClipMiddleRight, ClipMiddleTop};
	Vertices[8].TextureSize = {mBorderSize, mBorderSize};
	Vertices[8].InIndex = {mManager->mButtonCenterIn};
	Vertices[8].OutIndex = {mManager->mButtonCenterOut};
}

std::int16_t ButtonT::getLeft() const
{
	return mLeft;
}

std::int16_t ButtonT::getBottom() const
{
	return mBottom;
}

std::int16_t ButtonT::getRight() const
{
	return mRight;
}

std::int16_t ButtonT::getTop() const
{
	return mTop;
}

std::int16_t ButtonT::getClipLeft() const
{
	return mClipLeft;
}

std::int16_t ButtonT::getClipRight() const
{
	return mClipRight;
}

std::int16_t ButtonT::getClipBottom() const
{
	return mClipBottom;
}

std::int16_t ButtonT::getClipTop() const
{
	return mClipTop;
}

std::int16_t ButtonT::getBaseWidth(std::int16_t Width) const
{
	return Width + Settings::Button::BaseWidthMargin;
}

std::int16_t ButtonT::getBaseHeight(std::int16_t Height) const
{
	return Height + Settings::Button::BaseHeightMargin;
}

}
}
