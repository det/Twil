#include "Image.hpp"

#include "Ui/WindowBase.hpp"

namespace Twil {
namespace Theme {

void ImageT::init(Ui::WindowBaseT & Window)
{
	mWindow = &Window;
	mWindow->getThemeManager().mBitmapArray.allocate(*this, 1);
}

void ImageT::setImage(char const * Path)
{
	auto & Manager = mWindow->getThemeManager();
	auto Entry = Manager.loadBitmapEntry(Path);
	mOffset = Entry.Offset;
	mWidth = Entry.Width;
	mHeight = Entry.Height;
	Manager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipLeft(std::int32_t X)
{
	mClipLeft = X;
	mWindow->getThemeManager().mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipRight(std::int32_t X)
{
	mClipRight = X;
	mWindow->getThemeManager().mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipBottom(std::int32_t Y)
{
	mClipBottom = Y;
	mWindow->getThemeManager().mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipTop(std::int32_t Y)
{
	mClipTop = Y;
	mWindow->getThemeManager().mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::draw(Vertex::BitmapT * Vertices) const
{
	auto & Manager = mWindow->getThemeManager();

	// Avoid divide by 0
	if (mWidth == 0 || mHeight == 0)
	{
		Vertices[0] = {};
		return;
	}

	std::int16_t Left = mWindow->convertDipToPixelX(mLeft);
	std::int16_t Right = Left + mWidth;
	std::int16_t Bottom = mWindow->convertDipToPixelY(mBottom);
	std::int16_t Top = Bottom + mHeight;

	std::int16_t ClipLeft = mWindow->convertDipToPixelX(mClipLeft);
	std::int16_t ClipRight = mWindow->convertDipToPixelX(mClipRight);
	std::int16_t ClipBottom = mWindow->convertDipToPixelY(mClipBottom);
	std::int16_t ClipTop = mWindow->convertDipToPixelY(mClipTop);

	std::int16_t LeftClipped = Left;
	std::int16_t RightClipped = Right;
	std::int16_t BottomClipped = Bottom;
	std::int16_t TopClipped = Top;

	LeftClipped = std::max(LeftClipped, ClipLeft);
	RightClipped = std::max(RightClipped, ClipLeft);
	LeftClipped = std::min(LeftClipped, ClipRight);
	RightClipped = std::min(RightClipped, ClipRight);
	BottomClipped = std::max(BottomClipped, ClipBottom);
	TopClipped = std::max(TopClipped, ClipBottom);
	BottomClipped = std::min(BottomClipped, ClipTop);
	TopClipped = std::min(TopClipped, ClipTop);

	Vertices[0].ClipMin.S = (LeftClipped - Left) * 65535 / mWidth;
	Vertices[0].ClipMin.T = (BottomClipped - Bottom) * 65535 / mHeight;
	Vertices[0].ClipMax.S = (RightClipped - Left) * 65535 / mWidth;
	Vertices[0].ClipMax.T = (TopClipped - Bottom) * 65535 / mHeight;
	Vertices[0].PositionMin = {LeftClipped, BottomClipped};
	Vertices[0].PositionMax = {RightClipped, TopClipped};
	Vertices[0].TextureSize = {mWidth, mHeight};
	Vertices[0].Offset = {mOffset};
}

void ImageT::moveX(std::int32_t X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;

	mWindow->getThemeManager().mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::moveY(std::int32_t Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;

	mWindow->getThemeManager().mBitmapArray.markNeedsRedraw(*this);
}

std::int32_t ImageT::getLeft() const
{
	return mLeft;
}

std::int32_t ImageT::getBottom() const
{
	return mBottom;
}

std::int32_t ImageT::getRight() const
{
	return mLeft + getBaseWidth();
}

std::int32_t ImageT::getTop() const
{
	return mBottom + getBaseHeight();
}

std::int32_t ImageT::getClipLeft() const
{
	return mClipLeft;
}

std::int32_t ImageT::getClipRight() const
{
	return mClipRight;
}

std::int32_t ImageT::getClipBottom() const
{
	return mClipBottom;
}

std::int32_t ImageT::getClipTop() const
{
	return mClipTop;
}

std::int32_t ImageT::getBaseWidth() const
{
	return mWindow->convertPixelToDipX(mWidth);
}

std::int32_t ImageT::getBaseHeight() const
{
	return mWindow->convertPixelToDipY(mHeight);
}

}
}
