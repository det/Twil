#include "Centered.hpp"

#include <algorithm>

namespace Twil {
namespace Ui {

std::int32_t CenteredT::getLayoutLeft(std::int32_t Width) const
{
	return mLeft + (mRight - Width - mLeft) / 2;
}

std::int32_t CenteredT::getLayoutBottom(std::int32_t Height) const
{
	return mBottom + (mTop - Height - mBottom) / 2;
}

std::int32_t CenteredT::getLayoutClipLeft() const
{
	return std::max<std::int32_t>(mLeft, mClipLeft);
}

std::int32_t CenteredT::getLayoutClipRight() const
{
	return std::min<std::int32_t>(mRight, mClipRight);
}

std::int32_t CenteredT::getLayoutClipBottom() const
{
	return std::max<std::int32_t>(mBottom, mClipBottom);
}

std::int32_t CenteredT::getLayoutClipTop() const
{
	return std::min<std::int32_t>(mTop, mClipTop);
}

void CenteredT::setClipLeft(std::int32_t X)
{
	mClipLeft = X;
}

void CenteredT::setClipRight(std::int32_t X)
{
	mClipRight = X;
}

void CenteredT::setClipBottom(std::int32_t Y)
{
	mClipBottom = Y;
}

void CenteredT::setClipTop(std::int32_t Y)
{
	mClipTop = Y;
}

void CenteredT::moveX(std::int32_t X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
}

void CenteredT::moveY(std::int32_t Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
}

void CenteredT::resizeWidth(std::int32_t X)
{
	mRight += X;
	mClipRight += X;
}

void CenteredT::resizeHeight(std::int32_t Y)
{
	mTop += Y;
	mClipTop += Y;
}

std::int32_t CenteredT::getLeft() const
{
	return mLeft;
}

std::int32_t CenteredT::getRight() const
{
	return mRight;
}

std::int32_t CenteredT::getBottom() const
{
	return mBottom;
}

std::int32_t CenteredT::getTop() const
{
	return mTop;
}

std::int32_t CenteredT::getClipLeft() const
{
	return mClipLeft;
}

std::int32_t CenteredT::getClipRight() const
{
	return mClipRight;
}

std::int32_t CenteredT::getClipBottom() const
{
	return mClipBottom;
}

std::int32_t CenteredT::getClipTop() const
{
	return mClipTop;
}

}
}
