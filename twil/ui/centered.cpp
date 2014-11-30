#include "centered.hpp"

#include <algorithm>

namespace twil {
namespace ui {

Dip Centered::GetLayoutLeft(Dip width) const
{
	return left_ + (right_ - width - left_) / 2;
}

Dip Centered::GetLayoutBottom(Dip height) const
{
	return bottom_ + (top_ - height - bottom_) / 2;
}

Dip Centered::GetLayoutClipLeft() const
{
	return std::max(left_, clip_left_);
}

Dip Centered::GetLayoutClipRight() const
{
	return std::min(right_, clip_right_);
}

Dip Centered::GetLayoutClipBottom() const
{
	return std::max(bottom_, clip_bottom_);
}

Dip Centered::GetLayoutClipTop() const
{
	return std::min(top_, clip_top_);
}

void Centered::SetClipLeft(Dip x)
{
	clip_left_ = x;
}

void Centered::SetClipRight(Dip x)
{
	clip_right_ = x;
}

void Centered::SetClipBottom(Dip y)
{
	clip_bottom_ = y;
}

void Centered::SetClipTop(Dip y)
{
	clip_top_ = y;
}

void Centered::MoveX(Dip x)
{
	left_ += x;
	right_ += x;
	clip_left_ += x;
	clip_right_ += x;
}

void Centered::MoveY(Dip y)
{
	bottom_ += y;
	top_ += y;
	clip_bottom_ += y;
	clip_top_ += y;
}

void Centered::ResizeWidth(Dip x)
{
	right_ += x;
	clip_right_ += x;
}

void Centered::ResizeHeight(Dip y)
{
	top_ += y;
	clip_top_ += y;
}

Dip Centered::GetLeft() const
{
	return left_;
}

Dip Centered::GetRight() const
{
	return right_;
}

Dip Centered::GetBottom() const
{
	return bottom_;
}

Dip Centered::GetTop() const
{
	return top_;
}

Dip Centered::GetClipLeft() const
{
	return clip_left_;
}

Dip Centered::GetClipRight() const
{
	return clip_right_;
}

Dip Centered::GetClipBottom() const
{
	return clip_bottom_;
}

Dip Centered::GetClipTop() const
{
	return clip_top_;
}

}
}
