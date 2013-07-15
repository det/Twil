#include "Centered.hpp"

#include <algorithm>

namespace Twil {
namespace Ui {

std::int16_t CenteredT::getLayoutLeft(std::int16_t Width) const
{
	return mLeft + (mRight - Width - mLeft) / 2;
}

std::int16_t CenteredT::getLayoutBottom(std::int16_t Height) const
{
	return mBottom + (mTop - Height - mBottom) / 2;
}

std::int16_t CenteredT::getLayoutClipLeft() const
{
	return std::max<std::int16_t>(mLeft, mClipLeft);
}

std::int16_t CenteredT::getLayoutClipRight() const
{
	return std::min<std::int16_t>(mRight, mClipRight);
}

std::int16_t CenteredT::getLayoutClipBottom() const
{
	return std::max<std::int16_t>(mBottom, mClipBottom);
}

std::int16_t CenteredT::getLayoutClipTop() const
{
	return std::min<std::int16_t>(mTop, mClipTop);
}

void CenteredT::setClipLeft(std::int16_t X)
{
	mClipLeft = X;
}

void CenteredT::setClipRight(std::int16_t X)
{
	mClipRight = X;
}

void CenteredT::setClipBottom(std::int16_t Y)
{
	mClipBottom = Y;
}

void CenteredT::setClipTop(std::int16_t Y)
{
	mClipTop = Y;
}

void CenteredT::moveX(std::int16_t X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
}

void CenteredT::moveY(std::int16_t Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
}

void CenteredT::resizeWidth(std::int16_t X)
{
	mRight += X;
	mClipRight += X;
}

void CenteredT::resizeHeight(std::int16_t Y)
{
	mTop += Y;
	mClipTop += Y;
}

std::int16_t CenteredT::getLeft() const
{
	return mLeft;
}

std::int16_t CenteredT::getRight() const
{
	return mRight;
}

std::int16_t CenteredT::getBottom() const
{
	return mBottom;
}

std::int16_t CenteredT::getTop() const
{
	return mTop;
}

std::int16_t CenteredT::getClipLeft() const
{
	return mClipLeft;
}

std::int16_t CenteredT::getClipRight() const
{
	return mClipRight;
}

std::int16_t CenteredT::getClipBottom() const
{
	return mClipBottom;
}

std::int16_t CenteredT::getClipTop() const
{
	return mClipTop;
}

}
}
