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

signed short ButtonT::getLeftMargin() const
{
	return Settings::Button::LeftMargin;
}

signed short ButtonT::getRightMargin() const
{
	return Settings::Button::RightMargin;
}

signed short ButtonT::getBottomMargin() const
{
	return Settings::Button::BottomMargin;
}

signed short ButtonT::getTopMargin() const
{
	return Settings::Button::TopMargin;
}

void ButtonT::moveX(signed short X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::moveY(signed short Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::resizeWidth(signed short X)
{
	mRight += X;
	mClipRight += X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::resizeHeight(signed short Y)
{
	mTop += Y;
	mClipTop += Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipLeft(signed short X)
{
	mClipLeft = X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipRight(signed short X)
{
	mClipRight = X;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipBottom(signed short Y)
{
	mClipBottom = Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipTop(signed short Y)
{
	mClipTop = Y;
	mManager->mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::draw(Vertex::OutlineGradientT * Vertices) const
{
	signed short Left = mLeft;
	signed short MiddleLeft = mLeft + mCornerSize;
	signed short MiddleRight = mRight - mCornerSize;
	signed short Right = mRight;

	signed short Bottom = mBottom;
	signed short MiddleBottom = mBottom + mCornerSize;
	signed short MiddleTop = mTop - mCornerSize;
	signed short Top = mTop;

	signed short ClipLeft = Left;
	signed short ClipMiddleLeft = MiddleLeft;
	signed short ClipMiddleRight = MiddleRight;
	signed short ClipRight = Right;

	signed short ClipBottom = Bottom;
	signed short ClipMiddleBottom = MiddleBottom;
	signed short ClipMiddleTop = MiddleTop;
	signed short ClipTop = Top;

	signed short Height = mTop - mBottom;
	signed short CenterX = (Left + Right) / 2;
	signed short CenterY = (Bottom + Top) / 2;

	ClipMiddleLeft = std::min<signed short>(ClipMiddleLeft, CenterX);
	ClipMiddleRight = std::max<signed short>(ClipMiddleRight, CenterX);
	ClipMiddleBottom = std::min<signed short>(ClipMiddleBottom, CenterY);
	ClipMiddleTop = std::max<signed short>(ClipMiddleTop, CenterY);

	ClipLeft = std::max<signed short>(ClipLeft, mClipLeft);
	ClipMiddleLeft = std::max<signed short>(ClipMiddleLeft, mClipLeft);
	ClipMiddleRight = std::max<signed short>(ClipMiddleRight, mClipLeft);
	ClipRight = std::max<signed short>(ClipRight, mClipLeft);

	ClipLeft = std::min<signed short>(ClipLeft, mClipRight);
	ClipMiddleLeft = std::min<signed short>(ClipMiddleLeft, mClipRight);
	ClipMiddleRight = std::min<signed short>(ClipMiddleRight, mClipRight);
	ClipRight = std::min<signed short>(ClipRight, mClipRight);

	ClipBottom = std::min<signed short>(ClipBottom, mClipTop);
	ClipMiddleBottom = std::min<signed short>(ClipMiddleBottom, mClipTop);
	ClipMiddleTop = std::min<signed short>(ClipMiddleTop, mClipTop);
	ClipTop = std::min<signed short>(ClipTop, mClipTop);

	ClipBottom = std::max<signed short>(ClipBottom, mClipBottom);
	ClipMiddleBottom = std::max<signed short>(ClipMiddleBottom, mClipBottom);
	ClipMiddleTop = std::max<signed short>(ClipMiddleTop, mClipBottom);
	ClipTop = std::max<signed short>(ClipTop, mClipBottom);

	Attribute::Color4bT TopColor;
	Attribute::Color4bT MiddleBottomColor;
	Attribute::Color4bT MiddleTopColor;
	Attribute::Color4bT BottomColor;

	// Avoid divide by 0, the colors dont matter for 0 size rectangles
	if (Height != 0) {
		if (mIsDown) {
			TopColor = Settings::Button::TopDownColor;
			BottomColor = Settings::Button::BottomDownColor;
		}
		else {
			TopColor = Settings::Button::TopUpColor;
			BottomColor = Settings::Button::BottomUpColor;
		}

		MiddleBottomColor = mix(TopColor, BottomColor, (ClipMiddleBottom - Bottom) * 65535 / Height);
		MiddleTopColor = mix(TopColor, BottomColor, (ClipMiddleTop - Bottom) * 65535 / Height);
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
	Vertices[0].InsideIndex = {mManager->mButtonSwInside};
	Vertices[0].OutsideIndex = {mManager->mButtonSwOutside};

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
	Vertices[1].InsideIndex = {mManager->mButtonSeInside};
	Vertices[1].OutsideIndex = {mManager->mButtonSeOutside};

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
	Vertices[2].InsideIndex = {mManager->mButtonNeInside};
	Vertices[2].OutsideIndex = {mManager->mButtonNeOutside};

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
	Vertices[3].InsideIndex = {mManager->mButtonNwInside};
	Vertices[3].OutsideIndex = {mManager->mButtonNwOutside};

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
	Vertices[4].InsideIndex = {mManager->mButtonBottomInside};
	Vertices[4].OutsideIndex = {mManager->mButtonBottomOutside};

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
	Vertices[5].InsideIndex = {mManager->mButtonTopInside};
	Vertices[5].OutsideIndex = {mManager->mButtonTopOutside};

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
	Vertices[6].InsideIndex = {mManager->mButtonLeftInside};
	Vertices[6].OutsideIndex = {mManager->mButtonLeftOutside};

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
	Vertices[7].InsideIndex = {mManager->mButtonRightInside};
	Vertices[7].OutsideIndex = {mManager->mButtonRightOutside};

	Vertices[8].BorderColor = Settings::Button::BorderColor;
	Vertices[8].BottomColor = MiddleBottomColor;
	Vertices[8].TopColor = MiddleTopColor;
	Vertices[8].ClipMin = {0, 0};
	Vertices[8].ClipMax = {65535, 65535};
	Vertices[8].PositionMin = {ClipMiddleLeft, ClipMiddleBottom};
	Vertices[8].PositionMax = {ClipMiddleRight, ClipMiddleTop};
	Vertices[8].TextureSize = {mBorderSize, mBorderSize};
	Vertices[8].InsideIndex = {mManager->mButtonCenterInside};
	Vertices[8].OutsideIndex = {mManager->mButtonCenterOutside};
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

signed short ButtonT::getClipLeft() const
{
	return mClipLeft;
}

signed short ButtonT::getClipRight() const
{
	return mClipRight;
}

signed short ButtonT::getClipBottom() const
{
	return mClipBottom;
}

signed short ButtonT::getClipTop() const
{
	return mClipTop;
}

signed short ButtonT::getBaseWidth(signed short Width) const
{
	return Width + Settings::Button::BaseWidthMargin;
}

signed short ButtonT::getBaseHeight(signed short Height) const
{
	return Height + Settings::Button::BaseHeightMargin;
}

}
}
