#include "Centered.hpp"

#include <algorithm>

namespace Twil {
namespace Ui {

float CenteredT::getLayoutLeft(float Width) const
{
	return mLeft + (mRight - Width - mLeft) / 2;
}

float CenteredT::getLayoutBottom(float Height) const
{
	return mBottom + (mTop - Height - mBottom) / 2;
}

float CenteredT::getLayoutClipLeft() const
{
	return std::max<float>(mLeft, mClipLeft);
}

float CenteredT::getLayoutClipRight() const
{
	return std::min<float>(mRight, mClipRight);
}

float CenteredT::getLayoutClipBottom() const
{
	return std::max<float>(mBottom, mClipBottom);
}

float CenteredT::getLayoutClipTop() const
{
	return std::min<float>(mTop, mClipTop);
}

void CenteredT::setClipLeft(float X)
{
	mClipLeft = X;
}

void CenteredT::setClipRight(float X)
{
	mClipRight = X;
}

void CenteredT::setClipBottom(float Y)
{
	mClipBottom = Y;
}

void CenteredT::setClipTop(float Y)
{
	mClipTop = Y;
}

void CenteredT::moveX(float X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
}

void CenteredT::moveY(float Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
}

void CenteredT::resizeWidth(float X)
{
	mRight += X;
	mClipRight += X;
}

void CenteredT::resizeHeight(float Y)
{
	mTop += Y;
	mClipTop += Y;
}

float CenteredT::getLeft() const
{
	return mLeft;
}

float CenteredT::getRight() const
{
	return mRight;
}

float CenteredT::getBottom() const
{
	return mBottom;
}

float CenteredT::getTop() const
{
	return mTop;
}

float CenteredT::getClipLeft() const
{
	return mClipLeft;
}

float CenteredT::getClipRight() const
{
	return mClipRight;
}

float CenteredT::getClipBottom() const
{
	return mClipBottom;
}

float CenteredT::getClipTop() const
{
	return mClipTop;
}

}
}
