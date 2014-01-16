#include "Image.hpp"

#include "Manager.hpp"

namespace Twil {
namespace Theme {

void ImageT::init(ManagerT & Manager)
{
	mManager = &Manager;
	mManager->mBitmapArray.allocate(*this, 1);
}

void ImageT::setImage(char const * Path)
{
	auto Entry = mManager->loadBitmapEntry(Path);
	mOffset = Entry.Offset;
	mWidth = Entry.Width;
	mHeight = Entry.Height;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipLeft(float X)
{
	mClipLeft = X;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipRight(float X)
{
	mClipRight = X;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipBottom(float Y)
{
	mClipBottom = Y;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipTop(float Y)
{
	mClipTop = Y;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::draw(Vertex::BitmapT * Vertices) const
{
	// Avoid divide by 0
	if (mWidth == 0 || mHeight == 0)
	{
		Vertices[0] = {};
		return;
	}

	std::int16_t Left = mManager->fitHorizontalGrid(mLeft);
	std::int16_t Right = Left + mWidth;
	std::int16_t Bottom = mManager->fitVerticalGrid(mBottom);
	std::int16_t Top = Bottom + mHeight;

	std::int16_t ClipLeft = mManager->fitHorizontalGrid(mClipLeft);
	std::int16_t ClipRight = mManager->fitHorizontalGrid(mClipRight);
	std::int16_t ClipBottom = mManager->fitVerticalGrid(mClipBottom);
	std::int16_t ClipTop = mManager->fitVerticalGrid(mClipTop);

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

void ImageT::moveX(float X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;

	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::moveY(float Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;

	mManager->mBitmapArray.markNeedsRedraw(*this);
}

float ImageT::getLeft() const
{
	return mLeft;
}

float ImageT::getBottom() const
{
	return mBottom;
}

float ImageT::getRight() const
{
	return mLeft + getBaseWidth();
}

float ImageT::getTop() const
{
	return mBottom + getBaseHeight();
}

float ImageT::getClipLeft() const
{
	return mClipLeft;
}

float ImageT::getClipRight() const
{
	return mClipRight;
}

float ImageT::getClipBottom() const
{
	return mClipBottom;
}

float ImageT::getClipTop() const
{
	return mClipTop;
}

float ImageT::getBaseWidth() const
{
	return mWidth / Settings::Global::HorizontalScale;
}

float ImageT::getBaseHeight() const
{
	return mHeight / Settings::Global::VerticalScale;
}

}
}
