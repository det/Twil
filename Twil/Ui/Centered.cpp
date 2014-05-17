#include "Centered.hpp"

#include <algorithm>

namespace Twil {
namespace Ui {

DipT CenteredT::getLayoutLeft(DipT Width) const
{
	return mLeft + (mRight - Width - mLeft) / 2;
}

DipT CenteredT::getLayoutBottom(DipT Height) const
{
	return mBottom + (mTop - Height - mBottom) / 2;
}

DipT CenteredT::getLayoutClipLeft() const
{
	return std::max<DipT>(mLeft, mClipLeft);
}

DipT CenteredT::getLayoutClipRight() const
{
	return std::min<DipT>(mRight, mClipRight);
}

DipT CenteredT::getLayoutClipBottom() const
{
	return std::max<DipT>(mBottom, mClipBottom);
}

DipT CenteredT::getLayoutClipTop() const
{
	return std::min<DipT>(mTop, mClipTop);
}

void CenteredT::setClipLeft(DipT X)
{
	mClipLeft = X;
}

void CenteredT::setClipRight(DipT X)
{
	mClipRight = X;
}

void CenteredT::setClipBottom(DipT Y)
{
	mClipBottom = Y;
}

void CenteredT::setClipTop(DipT Y)
{
	mClipTop = Y;
}

void CenteredT::moveX(DipT X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;
}

void CenteredT::moveY(DipT Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;
}

void CenteredT::resizeWidth(DipT X)
{
	mRight += X;
	mClipRight += X;
}

void CenteredT::resizeHeight(DipT Y)
{
	mTop += Y;
	mClipTop += Y;
}

DipT CenteredT::getLeft() const
{
	return mLeft;
}

DipT CenteredT::getRight() const
{
	return mRight;
}

DipT CenteredT::getBottom() const
{
	return mBottom;
}

DipT CenteredT::getTop() const
{
	return mTop;
}

DipT CenteredT::getClipLeft() const
{
	return mClipLeft;
}

DipT CenteredT::getClipRight() const
{
	return mClipRight;
}

DipT CenteredT::getClipBottom() const
{
	return mClipBottom;
}

DipT CenteredT::getClipTop() const
{
	return mClipTop;
}

}
}
