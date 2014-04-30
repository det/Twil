#include "Button.hpp"

#include "Ui/WindowBase.hpp"
#include "Settings.hpp"

namespace Twil {
namespace Theme {

void ButtonT::init(Ui::WindowBaseT & Window)
{
	mWindow = &Window;
	mWindow->getThemeManager().mOutlineArray.allocate(*this, 9);
}

void ButtonT::setIsDown(bool IsDown)
{
	mIsDown = IsDown;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

float ButtonT::getLeftMargin() const
{
	return Settings::Button::LeftMargin;
}

float ButtonT::getRightMargin() const
{
	return Settings::Button::RightMargin;
}

float ButtonT::getBottomMargin() const
{
	return Settings::Button::BottomMargin;
}

float ButtonT::getTopMargin() const
{
	return Settings::Button::TopMargin;
}

void ButtonT::moveX(float X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::moveY(float Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::resizeWidth(float X)
{
	mRight += X;
	mClipRight += X;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::resizeHeight(float Y)
{
	mTop += Y;
	mClipTop += Y;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipLeft(float X)
{
	mClipLeft = X;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipRight(float X)
{
	mClipRight = X;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipBottom(float Y)
{
	mClipBottom = Y;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::setClipTop(float Y)
{
	mClipTop = Y;
	mWindow->getThemeManager().mOutlineArray.markNeedsRedraw(*this);
}

void ButtonT::draw(Vertex::OutlineGradientT * Vertices) const
{
	auto & Manager = mWindow->getThemeManager();

	std::uint16_t HorizontalCornerSize = Manager.mButtonHorizontalCornerSize;
	std::uint16_t VerticalCornerSize = Manager.mButtonVerticalCornerSize;

	std::int16_t Left = mWindow->convertDipToPixelX(mLeft);
	std::int16_t Right = mWindow->convertDipToPixelX(mRight);
	std::int16_t MiddleLeft = Left + HorizontalCornerSize;
	std::int16_t MiddleRight = Right - HorizontalCornerSize;

	std::int16_t ClipLeft = mWindow->convertDipToPixelX(mClipLeft);
	std::int16_t ClipRight = mWindow->convertDipToPixelX(mClipRight);
	std::int16_t ClipBottom = mWindow->convertDipToPixelY(mClipBottom);
	std::int16_t ClipTop = mWindow->convertDipToPixelY(mClipTop);

	std::int16_t Bottom = mWindow->convertDipToPixelY(mBottom);
	std::int16_t Top = mWindow->convertDipToPixelY(mTop);
	std::int16_t MiddleBottom = Bottom + VerticalCornerSize;
	std::int16_t MiddleTop = Top - VerticalCornerSize;

	std::int16_t LeftClipped = Left;
	std::int16_t MiddleLeftClipped = MiddleLeft;
	std::int16_t MiddleRightClipped = MiddleRight;
	std::int16_t RightClipped = Right;

	std::int16_t BottomClipped = Bottom;
	std::int16_t MiddleBottomClipped = MiddleBottom;
	std::int16_t MiddleTopClipped = MiddleTop;
	std::int16_t TopClipped = Top;

	std::int16_t Height = Top - Bottom;
	std::int16_t CenterX = (Left + Right) / 2;
	std::int16_t CenterY = (Bottom + Top) / 2;

	MiddleLeftClipped = std::min(MiddleLeftClipped, CenterX);
	MiddleRightClipped = std::max(MiddleRightClipped, CenterX);
	MiddleBottomClipped = std::min(MiddleBottomClipped, CenterY);
	MiddleTopClipped = std::max(MiddleTopClipped, CenterY);

	LeftClipped = std::max(LeftClipped, ClipLeft);
	MiddleLeftClipped = std::max(MiddleLeftClipped, ClipLeft);
	MiddleRightClipped = std::max(MiddleRightClipped, ClipLeft);
	RightClipped = std::max(RightClipped, ClipLeft);

	LeftClipped = std::min(LeftClipped, ClipRight);
	MiddleLeftClipped = std::min(MiddleLeftClipped, ClipRight);
	MiddleRightClipped = std::min(MiddleRightClipped, ClipRight);
	RightClipped = std::min(RightClipped, ClipRight);

	BottomClipped = std::min(BottomClipped, ClipTop);
	MiddleBottomClipped = std::min(MiddleBottomClipped, ClipTop);
	MiddleTopClipped = std::min(MiddleTopClipped, ClipTop);
	TopClipped = std::min(TopClipped, ClipTop);

	BottomClipped = std::max(BottomClipped, ClipBottom);
	MiddleBottomClipped = std::max(MiddleBottomClipped, ClipBottom);
	MiddleTopClipped = std::max(MiddleTopClipped, ClipBottom);
	TopClipped = std::max(TopClipped, ClipBottom);

	Attribute::Color4bT TopColor;
	Attribute::Color4bT MiddleBottomColor;
	Attribute::Color4bT MiddleTopColor;
	Attribute::Color4bT BottomColor;

	// Avoid divide by 0, the colors dont matter for 0 size rectangles
	if (Height != 0.0f)
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
			(MiddleBottomClipped - Bottom) * 65535 / Height);

		MiddleTopColor = mix(
			TopColor,
			BottomColor,
			(MiddleTopClipped - Bottom) * 65535 / Height);
	}

	Vertices[0].BorderColor = Settings::Button::BorderColor;
	Vertices[0].BottomColor = BottomColor;
	Vertices[0].TopColor = MiddleBottomColor;
	Vertices[0].ClipMin.S = (LeftClipped - Left) * 65535 / HorizontalCornerSize;
	Vertices[0].ClipMin.T = (BottomClipped - Bottom) * 65535 / VerticalCornerSize;
	Vertices[0].ClipMax.S = (MiddleLeftClipped - Left) * 65535 / HorizontalCornerSize;
	Vertices[0].ClipMax.T = (MiddleBottomClipped - Bottom) * 65535 / VerticalCornerSize;
	Vertices[0].PositionMin = {LeftClipped, BottomClipped};
	Vertices[0].PositionMax = {MiddleLeftClipped, MiddleBottomClipped};
	Vertices[0].TextureSize = {HorizontalCornerSize, VerticalCornerSize};
	Vertices[0].InIndex = {Manager.mButtonSwIn};
	Vertices[0].OutIndex = {Manager.mButtonSwOut};

	Vertices[1].BorderColor = Settings::Button::BorderColor;
	Vertices[1].BottomColor = BottomColor;
	Vertices[1].TopColor = MiddleBottomColor;
	Vertices[1].ClipMin.S = (MiddleRightClipped - MiddleRight) * 65535 / HorizontalCornerSize;
	Vertices[1].ClipMin.T = (BottomClipped - Bottom) * 65535 / VerticalCornerSize;
	Vertices[1].ClipMax.S = (RightClipped - MiddleRight) * 65535 / HorizontalCornerSize;
	Vertices[1].ClipMax.T = (MiddleBottomClipped - Bottom) * 65535 / VerticalCornerSize;
	Vertices[1].PositionMin = {MiddleRightClipped, BottomClipped};
	Vertices[1].PositionMax = {RightClipped, MiddleBottomClipped};
	Vertices[1].TextureSize = {HorizontalCornerSize, VerticalCornerSize};
	Vertices[1].InIndex = {Manager.mButtonSeIn};
	Vertices[1].OutIndex = {Manager.mButtonSeOut};

	Vertices[2].BorderColor = Settings::Button::BorderColor;
	Vertices[2].BottomColor = MiddleTopColor;
	Vertices[2].TopColor = TopColor;
	Vertices[2].ClipMin.S = (MiddleRightClipped - MiddleRight) * 65535 / HorizontalCornerSize;
	Vertices[2].ClipMin.T = (MiddleTopClipped - MiddleTop) * 65535 / VerticalCornerSize;
	Vertices[2].ClipMax.S = (RightClipped - MiddleRight) * 65535 / HorizontalCornerSize;
	Vertices[2].ClipMax.T = (TopClipped - MiddleTop) * 65535 / VerticalCornerSize;
	Vertices[2].PositionMin = {MiddleRightClipped, MiddleTopClipped};
	Vertices[2].PositionMax = {RightClipped, TopClipped};
	Vertices[2].TextureSize = {HorizontalCornerSize, VerticalCornerSize};
	Vertices[2].InIndex = {Manager.mButtonNeIn};
	Vertices[2].OutIndex = {Manager.mButtonNeOut};

	Vertices[3].BorderColor = Settings::Button::BorderColor;
	Vertices[3].BottomColor = MiddleTopColor;
	Vertices[3].TopColor = TopColor;
	Vertices[3].ClipMin.S = (LeftClipped - Left) * 65535 / HorizontalCornerSize;
	Vertices[3].ClipMin.T = (MiddleTopClipped - MiddleTop) * 65535 / VerticalCornerSize;
	Vertices[3].ClipMax.S = (MiddleLeftClipped - Left) * 65535 / HorizontalCornerSize;
	Vertices[3].ClipMax.T = (TopClipped - MiddleTop) * 65535 / VerticalCornerSize;
	Vertices[3].PositionMin = {LeftClipped, MiddleTopClipped};
	Vertices[3].PositionMax = {MiddleLeftClipped, TopClipped};
	Vertices[3].TextureSize = {HorizontalCornerSize, VerticalCornerSize};
	Vertices[3].InIndex = {Manager.mButtonNwIn};
	Vertices[3].OutIndex = {Manager.mButtonNwOut};

	Vertices[4].BorderColor = Settings::Button::BorderColor;
	Vertices[4].BottomColor = BottomColor;
	Vertices[4].TopColor = MiddleBottomColor;
	Vertices[4].ClipMin.S = 0;
	Vertices[4].ClipMin.T = (BottomClipped - Bottom) * 65535 / VerticalCornerSize;
	Vertices[4].ClipMax.S = 65535;
	Vertices[4].ClipMax.T = (MiddleBottomClipped - Bottom) * 65535 / VerticalCornerSize;
	Vertices[4].PositionMin = {MiddleLeftClipped, BottomClipped};
	Vertices[4].PositionMax = {MiddleRightClipped, MiddleBottomClipped};
	Vertices[4].TextureSize = {1, VerticalCornerSize};
	Vertices[4].InIndex = {Manager.mButtonBottomIn};
	Vertices[4].OutIndex = {Manager.mButtonBottomOut};

	Vertices[5].BorderColor = Settings::Button::BorderColor;
	Vertices[5].BottomColor = MiddleTopColor;
	Vertices[5].TopColor = TopColor;
	Vertices[5].ClipMin.S = 0;
	Vertices[5].ClipMin.T = (MiddleTopClipped - MiddleTop) * 65535 / VerticalCornerSize;
	Vertices[5].ClipMax.S = 65535;
	Vertices[5].ClipMax.T = (TopClipped - MiddleTop) * 65535 / VerticalCornerSize;
	Vertices[5].PositionMin = {MiddleLeftClipped, MiddleTopClipped};
	Vertices[5].PositionMax = {MiddleRightClipped, TopClipped};
	Vertices[5].TextureSize = {1, VerticalCornerSize};
	Vertices[5].InIndex = {Manager.mButtonTopIn};
	Vertices[5].OutIndex = {Manager.mButtonTopOut};

	Vertices[6].BorderColor = Settings::Button::BorderColor;
	Vertices[6].BottomColor = MiddleBottomColor;
	Vertices[6].TopColor = MiddleTopColor;
	Vertices[6].ClipMin.S = (LeftClipped - Left) * 65535 / HorizontalCornerSize;
	Vertices[6].ClipMin.T = 0;
	Vertices[6].ClipMax.S = (MiddleLeftClipped - Left) * 65535 / HorizontalCornerSize;
	Vertices[6].ClipMax.T = 65535;
	Vertices[6].PositionMin = {LeftClipped, MiddleBottomClipped};
	Vertices[6].PositionMax = {MiddleLeftClipped, MiddleTopClipped};
	Vertices[6].TextureSize = {HorizontalCornerSize, 1};
	Vertices[6].InIndex = {Manager.mButtonLeftIn};
	Vertices[6].OutIndex = {Manager.mButtonLeftOut};

	Vertices[7].BorderColor = Settings::Button::BorderColor;
	Vertices[7].BottomColor = MiddleBottomColor;
	Vertices[7].TopColor = MiddleTopColor;
	Vertices[7].ClipMin.S = (MiddleRightClipped - MiddleRight) * 65535 / HorizontalCornerSize;
	Vertices[7].ClipMin.T = 0;
	Vertices[7].ClipMax.S = (RightClipped - MiddleRight) * 65535 / HorizontalCornerSize;
	Vertices[7].ClipMax.T = 65535;
	Vertices[7].PositionMin = {MiddleRightClipped, MiddleBottomClipped};
	Vertices[7].PositionMax = {RightClipped, MiddleTopClipped};
	Vertices[7].TextureSize = {HorizontalCornerSize, 1};
	Vertices[7].InIndex = {Manager.mButtonRightIn};
	Vertices[7].OutIndex = {Manager.mButtonRightOut};

	Vertices[8].BorderColor = Settings::Button::BorderColor;
	Vertices[8].BottomColor = MiddleBottomColor;
	Vertices[8].TopColor = MiddleTopColor;
	Vertices[8].ClipMin = {0, 0};
	Vertices[8].ClipMax = {65535, 65535};
	Vertices[8].PositionMin = {MiddleLeftClipped, MiddleBottomClipped};
	Vertices[8].PositionMax = {MiddleRightClipped, MiddleTopClipped};
	Vertices[8].TextureSize = {1, 1};
	Vertices[8].InIndex = {Manager.mButtonCenterIn};
	Vertices[8].OutIndex = {Manager.mButtonCenterOut};
}

float ButtonT::getLeft() const
{
	return mLeft;
}

float ButtonT::getBottom() const
{
	return mBottom;
}

float ButtonT::getRight() const
{
	return mRight;
}

float ButtonT::getTop() const
{
	return mTop;
}

float ButtonT::getClipLeft() const
{
	return mClipLeft;
}

float ButtonT::getClipRight() const
{
	return mClipRight;
}

float ButtonT::getClipBottom() const
{
	return mClipBottom;
}

float ButtonT::getClipTop() const
{
	return mClipTop;
}

float ButtonT::getBaseWidth(float Width) const
{
	return Width + Settings::Button::BaseWidthMargin;
}

float ButtonT::getBaseHeight(float Height) const
{
	return Height + Settings::Button::BaseHeightMargin;
}

}
}
