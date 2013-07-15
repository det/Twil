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

void ImageT::setClipLeft(std::int16_t X)
{
	mClipLeft = X;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipRight(std::int16_t X)
{
	mClipRight = X;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipBottom(std::int16_t Y)
{
	mClipBottom = Y;
	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipTop(std::int16_t Y)
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

	std::int16_t PositionLeft = mLeft;
	std::int16_t PositionRight = mLeft + mWidth;
	std::int16_t PositionBottom = mBottom;
	std::int16_t PositionTop = mBottom + mHeight;

	std::int16_t Width = mWidth;
	std::int16_t Height = mHeight;

	std::int16_t ClipLeft = PositionLeft;
	std::int16_t ClipRight = PositionRight;
	std::int16_t ClipBottom = PositionBottom;
	std::int16_t ClipTop = PositionTop;

	ClipLeft = std::max<std::int16_t>(ClipLeft, mClipLeft);
	ClipRight = std::max<std::int16_t>(ClipRight, mClipLeft);
	ClipLeft = std::min<std::int16_t>(ClipLeft, mClipRight);
	ClipRight = std::min<std::int16_t>(ClipRight, mClipRight);
	ClipBottom = std::max<std::int16_t>(ClipBottom, mClipBottom);
	ClipTop = std::max<std::int16_t>(ClipTop, mClipBottom);
	ClipBottom = std::min<std::int16_t>(ClipBottom, mClipTop);
	ClipTop = std::min<std::int16_t>(ClipTop, mClipTop);

	Vertices[0].ClipMin.S = (ClipLeft - PositionLeft) * 65535 / Width;
	Vertices[0].ClipMin.T = (ClipBottom - PositionBottom) * 65535 / Height;
	Vertices[0].ClipMax.S = (ClipRight - PositionLeft) * 65535 / Width;
	Vertices[0].ClipMax.T = (ClipTop - PositionBottom) * 65535 / Height;
	Vertices[0].PositionMin = {ClipLeft, ClipBottom};
	Vertices[0].PositionMax = {ClipRight, ClipTop};
	Vertices[0].TextureSize = {GLushort(mWidth), GLushort(mHeight)};
	Vertices[0].Offset = {mOffset};
}

void ImageT::moveX(std::int16_t X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;

	mManager->mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::moveY(std::int16_t Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;

	mManager->mBitmapArray.markNeedsRedraw(*this);
}

std::int16_t ImageT::getLeft() const
{
	return mLeft;
}

std::int16_t ImageT::getBottom() const
{
	return mBottom;
}

std::int16_t ImageT::getRight() const
{
	return mLeft + mWidth;
}

std::int16_t ImageT::getTop() const
{
	return mBottom + mHeight;
}

std::int16_t ImageT::getClipLeft() const
{
	return mClipLeft;
}

std::int16_t ImageT::getClipRight() const
{
	return mClipRight;
}

std::int16_t ImageT::getClipBottom() const
{
	return mClipBottom;
}

std::int16_t ImageT::getClipTop() const
{
	return mClipTop;
}

std::int16_t ImageT::getBaseWidth() const
{
	return mWidth;
}

std::int16_t ImageT::getBaseHeight() const
{
	return mHeight;
}

}
}
