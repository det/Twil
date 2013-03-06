#include "Centered.hpp"

#include <algorithm>

namespace Twil {
namespace Ui {

signed short CenteredT::getLayoutLeft(signed short Width) const
{
	return mLeft + (mRight - Width - mLeft) / 2;
}

signed short CenteredT::getLayoutBottom(signed short Height) const
{
	return mBottom + (mTop - Height - mBottom) / 2;
}

signed short CenteredT::getLayoutClipLeft() const
{
	return std::max<signed short>(mLeft, mClipLeft);
}

signed short CenteredT::getLayoutClipRight() const
{
	return std::min<signed short>(mRight, mClipRight);
}

signed short CenteredT::getLayoutClipBottom() const
{
	return std::max<signed short>(mBottom, mClipBottom);
}

signed short CenteredT::getLayoutClipTop() const
{
	return std::min<signed short>(mTop, mClipTop);
}

void CenteredT::setClipLeft(signed short X)
{
	mClipLeft = X;
}

void CenteredT::setClipRight(signed short X)
{
	mClipRight = X;
}

void CenteredT::setClipBottom(signed short Y)
{
	mClipBottom = Y;
}

void CenteredT::setClipTop(signed short Y)
{
	mClipTop = Y;
}

void CenteredT::moveX(signed short X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
}

void CenteredT::moveY(signed short Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
}

void CenteredT::resizeWidth(signed short X)
{
	mRight += X;
	mClipRight += X;
}

void CenteredT::resizeHeight(signed short Y)
{
	mTop += Y;
	mClipTop += Y;
}

signed short CenteredT::getLeft() const
{
	return mLeft;
}

signed short CenteredT::getRight() const
{
	return mRight;
}

signed short CenteredT::getBottom() const
{
	return mBottom;
}

signed short CenteredT::getTop() const
{
	return mTop;
}

signed short CenteredT::getClipLeft() const
{
	return mClipLeft;
}

signed short CenteredT::getClipRight() const
{
	return mClipRight;
}

signed short CenteredT::getClipBottom() const
{
	return mClipBottom;
}

signed short CenteredT::getClipTop() const
{
	return mClipTop;
}

}
}
