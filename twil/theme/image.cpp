#include "image.hpp"

#include "ui/window_base.hpp"

namespace twil {
namespace theme {

void Image::Init(ui::WindowBase & window)
{
	window_ = &window;
	window_->GetThemeManager().bitmap_array_.Allocate(*this, 1);
}

void Image::SetImage(char const * path)
{
	auto & manager = window_->GetThemeManager();
	auto entry = manager.LoadBitmapEntry(path);
	offset_ = entry.offset;
	width_ = entry.width;
	height_ = entry.height;
	manager.bitmap_array_.MarkNeedsRedraw(*this);
}

void Image::SetClipLeft(ui::Dip x)
{
	clip_left_ = x;
	window_->GetThemeManager().bitmap_array_.MarkNeedsRedraw(*this);
}

void Image::SetClipRight(ui::Dip x)
{
	clip_right_ = x;
	window_->GetThemeManager().bitmap_array_.MarkNeedsRedraw(*this);
}

void Image::SetClipBottom(ui::Dip y)
{
	clip_bottom_ = y;
	window_->GetThemeManager().bitmap_array_.MarkNeedsRedraw(*this);
}

void Image::SetClipTop(ui::Dip y)
{
	clip_top_ = y;
	window_->GetThemeManager().bitmap_array_.MarkNeedsRedraw(*this);
}

void Image::Draw(vertex::Bitmap * vertices) const
{
	// Avoid divide by 0
	if (width_ == 0 || height_ == 0)
	{
		vertices[0] = {};
		return;
	}

	ui::Pixel left = window_->ConvertDipToPixelX(left_);
	ui::Pixel right = left + width_;
	ui::Pixel bottom = window_->ConvertDipToPixelY(bottom_);
	ui::Pixel top = bottom + height_;

	ui::Pixel clip_left = window_->ConvertDipToPixelX(clip_left_);
	ui::Pixel clip_right = window_->ConvertDipToPixelX(clip_right_);
	ui::Pixel clip_bottom = window_->ConvertDipToPixelY(clip_bottom_);
	ui::Pixel clip_top = window_->ConvertDipToPixelY(clip_top_);

	ui::Pixel left_clipped = left;
	ui::Pixel right_clipped = right;
	ui::Pixel bottom_clipped = bottom;
	ui::Pixel top_clipped = top;

	left_clipped = std::max(left_clipped, clip_left);
	right_clipped = std::max(right_clipped, clip_left);
	left_clipped = std::min(left_clipped, clip_right);
	right_clipped = std::min(right_clipped, clip_right);
	bottom_clipped = std::max(bottom_clipped, clip_bottom);
	top_clipped = std::max(top_clipped, clip_bottom);
	bottom_clipped = std::min(bottom_clipped, clip_top);
	top_clipped = std::min(top_clipped, clip_top);

	vertices[0].clip_min.s = (left_clipped - left) * 65535 / width_;
	vertices[0].clip_min.t = (bottom_clipped - bottom) * 65535 / height_;
	vertices[0].clip_max.s = (right_clipped - left) * 65535 / width_;
	vertices[0].clip_max.t = (top_clipped - bottom) * 65535 / height_;
	vertices[0].position_min = {left_clipped, bottom_clipped};
	vertices[0].position_max = {right_clipped, top_clipped};
	vertices[0].texture_size = {width_, height_};
	vertices[0].offset = {offset_};
}

void Image::MoveX(ui::Dip x)
{
	left_ += x;
	clip_left_ += x;
	clip_right_ += x;

	window_->GetThemeManager().bitmap_array_.MarkNeedsRedraw(*this);
}

void Image::MoveY(ui::Dip y)
{
	bottom_ += y;
	clip_bottom_ += y;
	clip_top_ += y;

	window_->GetThemeManager().bitmap_array_.MarkNeedsRedraw(*this);
}

ui::Dip Image::GetLeft() const
{
	return left_;
}

ui::Dip Image::GetBottom() const
{
	return bottom_;
}

ui::Dip Image::GetRight() const
{
	return left_ + GetBaseWidth();
}

ui::Dip Image::GetTop() const
{
	return bottom_ + GetBaseHeight();
}

ui::Dip Image::GetClipLeft() const
{
	return clip_left_;
}

ui::Dip Image::GetClipRight() const
{
	return clip_right_;
}

ui::Dip Image::GetClipBottom() const
{
	return clip_bottom_;
}

ui::Dip Image::GetClipTop() const
{
	return clip_top_;
}

ui::Dip Image::GetBaseWidth() const
{
	return window_->ConvertPixelToDipX(width_);
}

ui::Dip Image::GetBaseHeight() const
{
	return window_->ConvertPixelToDipY(height_);
}

}
}
