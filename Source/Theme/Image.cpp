#include "Image.hpp"

#include "Manager.hpp"

namespace Twil {
namespace Theme {

ImageT::ImageT(ManagerT & Manager) :
	mManager(Manager) // Gcc bug prevents brace initialization syntax here
{
	mManager.mBitmapArray.allocate(*this, 1);
}

void ImageT::setImage(char const * Path)
{
	auto Entry = mManager.loadBitmapEntry(Path);
	mOffset = Entry.Offset;
	mWidth = Entry.Width;
	mHeight = Entry.Height;
	mManager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipLeft(signed short X)
{
	mClipLeft = X;
	mManager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipRight(signed short X)
{
	mClipRight = X;
	mManager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipBottom(signed short Y)
{
	mClipBottom = Y;
	mManager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::setClipTop(signed short Y)
{
	mClipTop = Y;
	mManager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::draw(Vertex::BitmapT * Vertices) const
{
	// Avoid divide by 0
	if (mWidth == 0 || mHeight == 0) {
		Vertices[0] = {}; // Zero-initizialize
		return;
	}

	signed short PositionLeft = mLeft;
	signed short PositionRight = mLeft + mWidth;
	signed short PositionBottom = mBottom;
	signed short PositionTop = mBottom + mHeight;

	signed short Width = mWidth;
	signed short Height = mHeight;

	signed short ClipLeft = PositionLeft;
	signed short ClipRight = PositionRight;
	signed short ClipBottom = PositionBottom;
	signed short ClipTop = PositionTop;

	ClipLeft = std::max<signed short>(ClipLeft, mClipLeft);
	ClipRight = std::max<signed short>(ClipRight, mClipLeft);
	ClipLeft = std::min<signed short>(ClipLeft, mClipRight);
	ClipRight = std::min<signed short>(ClipRight, mClipRight);
	ClipBottom = std::max<signed short>(ClipBottom, mClipBottom);
	ClipTop = std::max<signed short>(ClipTop, mClipBottom);
	ClipBottom = std::min<signed short>(ClipBottom, mClipTop);
	ClipTop = std::min<signed short>(ClipTop, mClipTop);

	Vertices[0].ClipMin.S = (ClipLeft - PositionLeft) * 65535 / Width;
	Vertices[0].ClipMin.T = (ClipBottom - PositionBottom) * 65535 / Height;
	Vertices[0].ClipMax.S = (ClipRight - PositionLeft) * 65535 / Width;
	Vertices[0].ClipMax.T = (ClipTop - PositionBottom) * 65535 / Height;
	Vertices[0].PositionMin = {ClipLeft, ClipBottom};
	Vertices[0].PositionMax = {ClipRight, ClipTop};
	Vertices[0].TextureSize = {GLushort(mWidth), GLushort(mHeight)};
	Vertices[0].Offset = {mOffset};
}

void ImageT::moveX(signed short X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;

	mManager.mBitmapArray.markNeedsRedraw(*this);
}

void ImageT::moveY(signed short Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;

	mManager.mBitmapArray.markNeedsRedraw(*this);
}

signed short ImageT::getLeft() const
{
	return mLeft;
}

signed short ImageT::getBottom() const
{
	return mBottom;
}

signed short ImageT::getRight() const
{
	return mLeft + mWidth;
}

signed short ImageT::getTop() const
{
	return mBottom + mHeight;
}

signed short ImageT::getClipLeft() const
{
	return mClipLeft;
}

signed short ImageT::getClipRight() const
{
	return mClipRight;
}

signed short ImageT::getClipBottom() const
{
	return mClipBottom;
}

signed short ImageT::getClipTop() const
{
	return mClipTop;
}

signed short ImageT::getBaseWidth() const
{
	return mWidth;
}

signed short ImageT::getBaseHeight() const
{
	return mHeight;
}

}
}
