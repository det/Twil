#include "button.hpp"

#include "ui/unit.hxx"
#include "ui/window_base.hpp"
#include "settings.hpp"

namespace twil {
namespace theme {

void Button::Init(ui::WindowBase & window)
{
	window_ = &window;
	window_->GetThemeManager().outline_array_.Allocate(*this, 9);
}

void Button::SetIsDown(bool is_down)
{
	is_down_ = is_down;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

ui::Dip Button::GetLeftMargin() const
{
	return settings::button::left_margin;
}

ui::Dip Button::GetRightMargin() const
{
	return settings::button::right_margin;
}

ui::Dip Button::GetBottomMargin() const
{
	return settings::button::bottom_margin;
}

ui::Dip Button::GetTopMargin() const
{
	return settings::button::top_margin;
}

void Button::MoveX(ui::Dip x)
{
	left_ += x;
	right_ += x;
	clip_left_ += x;
	clip_right_ += x;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::MoveY(ui::Dip y)
{
	bottom_ += y;
	top_ += y;
	clip_bottom_ += y;
	clip_top_ += y;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::ResizeWidth(ui::Dip x)
{
	right_ += x;
	clip_right_ += x;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::ResizeHeight(ui::Dip y)
{
	top_ += y;
	clip_top_ += y;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::SetClipLeft(ui::Dip x)
{
	clip_left_ = x;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::SetClipRight(ui::Dip x)
{
	clip_right_ = x;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::SetClipBottom(ui::Dip y)
{
	clip_bottom_ = y;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::SetClipTop(ui::Dip y)
{
	clip_top_ = y;
	window_->GetThemeManager().outline_array_.MarkNeedsRedraw(*this);
}

void Button::Draw(vertex::OutlineGradient * vertices) const
{
	auto & manager = window_->GetThemeManager();

	std::uint16_t horizontal_corner_size = manager.button_horizontal_corner_size_;
	std::uint16_t vertical_corner_size = manager.button_vertical_corner_size_;

	ui::Pixel left = window_->ConvertDipToPixelX(left_);
	ui::Pixel right = window_->ConvertDipToPixelX(right_);
	ui::Pixel middle_left = left + horizontal_corner_size;
	ui::Pixel middle_right = right - horizontal_corner_size;

	ui::Pixel clip_left = window_->ConvertDipToPixelX(clip_left_);
	ui::Pixel clip_right = window_->ConvertDipToPixelX(clip_right_);
	ui::Pixel clip_bottom = window_->ConvertDipToPixelY(clip_bottom_);
	ui::Pixel clip_top = window_->ConvertDipToPixelY(clip_top_);

	ui::Pixel bottom = window_->ConvertDipToPixelY(bottom_);
	ui::Pixel top = window_->ConvertDipToPixelY(top_);
	ui::Pixel middle_bottom = bottom + vertical_corner_size;
	ui::Pixel middle_top = top - vertical_corner_size;

	ui::Pixel left_clipped = left;
	ui::Pixel middle_left_clipped = middle_left;
	ui::Pixel middle_right_clipped = middle_right;
	ui::Pixel right_clipped = right;

	ui::Pixel bottom_clipped = bottom;
	ui::Pixel middle_bottom_clipped = middle_bottom;
	ui::Pixel middle_top_clipped = middle_top;
	ui::Pixel top_clipped = top;

	ui::Pixel height = top - bottom;
	ui::Pixel center_x = (left + right) / 2;
	ui::Pixel center_y = (bottom + top) / 2;

	middle_left_clipped = std::min(middle_left_clipped, center_x);
	middle_right_clipped = std::max(middle_right_clipped, center_x);
	middle_bottom_clipped = std::min(middle_bottom_clipped, center_y);
	middle_top_clipped = std::max(middle_top_clipped, center_y);

	left_clipped = std::max(left_clipped, clip_left);
	middle_left_clipped = std::max(middle_left_clipped, clip_left);
	middle_right_clipped = std::max(middle_right_clipped, clip_left);
	right_clipped = std::max(right_clipped, clip_left);

	left_clipped = std::min(left_clipped, clip_right);
	middle_left_clipped = std::min(middle_left_clipped, clip_right);
	middle_right_clipped = std::min(middle_right_clipped, clip_right);
	right_clipped = std::min(right_clipped, clip_right);

	bottom_clipped = std::min(bottom_clipped, clip_top);
	middle_bottom_clipped = std::min(middle_bottom_clipped, clip_top);
	middle_top_clipped = std::min(middle_top_clipped, clip_top);
	top_clipped = std::min(top_clipped, clip_top);

	bottom_clipped = std::max(bottom_clipped, clip_bottom);
	middle_bottom_clipped = std::max(middle_bottom_clipped, clip_bottom);
	middle_top_clipped = std::max(middle_top_clipped, clip_bottom);
	top_clipped = std::max(top_clipped, clip_bottom);

	attribute::Color4B top_color;
	attribute::Color4B middle_bottom_color;
	attribute::Color4B middle_top_color;
	attribute::Color4B bottom_color;

	// Avoid divide by 0, the colors dont matter for 0 size rectangles
	if (height != 0)
	{
		if (is_down_)
		{
			top_color = settings::button::top_down_color;
			bottom_color = settings::button::bottom_down_color;
		}
		else
		{
			top_color = settings::button::top_up_color;
			bottom_color = settings::button::bottom_up_color;
		}

		middle_bottom_color =	Mix(
			top_color,
			bottom_color,
			(middle_bottom_clipped - bottom) * 65535 / height);

		middle_top_color = Mix(
			top_color,
			bottom_color,
			(middle_top_clipped - bottom) * 65535 / height);
	}

	vertices[0].border_color = settings::button::border_color;
	vertices[0].bottom_color = bottom_color;
	vertices[0].top_color = middle_bottom_color;
	vertices[0].clip_min.s = (left_clipped - left) * 65535 / horizontal_corner_size;
	vertices[0].clip_min.t = (bottom_clipped - bottom) * 65535 / vertical_corner_size;
	vertices[0].clip_max.s = (middle_left_clipped - left) * 65535 / horizontal_corner_size;
	vertices[0].clip_max.t = (middle_bottom_clipped - bottom) * 65535 / vertical_corner_size;
	vertices[0].position_min = {left_clipped, bottom_clipped};
	vertices[0].position_max = {middle_left_clipped, middle_bottom_clipped};
	vertices[0].texture_size = {horizontal_corner_size, vertical_corner_size};
	vertices[0].in_index = {manager.button_sw_in_};
	vertices[0].out_index = {manager.button_sw_out};

	vertices[1].border_color = settings::button::border_color;
	vertices[1].bottom_color = bottom_color;
	vertices[1].top_color = middle_bottom_color;
	vertices[1].clip_min.s = (middle_right_clipped - middle_right) * 65535 / horizontal_corner_size;
	vertices[1].clip_min.t = (bottom_clipped - bottom) * 65535 / vertical_corner_size;
	vertices[1].clip_max.s = (right_clipped - middle_right) * 65535 / horizontal_corner_size;
	vertices[1].clip_max.t = (middle_bottom_clipped - bottom) * 65535 / vertical_corner_size;
	vertices[1].position_min = {middle_right_clipped, bottom_clipped};
	vertices[1].position_max = {right_clipped, middle_bottom_clipped};
	vertices[1].texture_size = {horizontal_corner_size, vertical_corner_size};
	vertices[1].in_index = {manager.button_se_in};
	vertices[1].out_index = {manager.button_se_out};

	vertices[2].border_color = settings::button::border_color;
	vertices[2].bottom_color = middle_top_color;
	vertices[2].top_color = top_color;
	vertices[2].clip_min.s = (middle_right_clipped - middle_right) * 65535 / horizontal_corner_size;
	vertices[2].clip_min.t = (middle_top_clipped - middle_top) * 65535 / vertical_corner_size;
	vertices[2].clip_max.s = (right_clipped - middle_right) * 65535 / horizontal_corner_size;
	vertices[2].clip_max.t = (top_clipped - middle_top) * 65535 / vertical_corner_size;
	vertices[2].position_min = {middle_right_clipped, middle_top_clipped};
	vertices[2].position_max = {right_clipped, top_clipped};
	vertices[2].texture_size = {horizontal_corner_size, vertical_corner_size};
	vertices[2].in_index = {manager.button_ne_in};
	vertices[2].out_index = {manager.button_ne_out};

	vertices[3].border_color = settings::button::border_color;
	vertices[3].bottom_color = middle_top_color;
	vertices[3].top_color = top_color;
	vertices[3].clip_min.s = (left_clipped - left) * 65535 / horizontal_corner_size;
	vertices[3].clip_min.t = (middle_top_clipped - middle_top) * 65535 / vertical_corner_size;
	vertices[3].clip_max.s = (middle_left_clipped - left) * 65535 / horizontal_corner_size;
	vertices[3].clip_max.t = (top_clipped - middle_top) * 65535 / vertical_corner_size;
	vertices[3].position_min = {left_clipped, middle_top_clipped};
	vertices[3].position_max = {middle_left_clipped, top_clipped};
	vertices[3].texture_size = {horizontal_corner_size, vertical_corner_size};
	vertices[3].in_index = {manager.button_nw_in};
	vertices[3].out_index = {manager.button_nw_out};

	vertices[4].border_color = settings::button::border_color;
	vertices[4].bottom_color = bottom_color;
	vertices[4].top_color = middle_bottom_color;
	vertices[4].clip_min.s = 0;
	vertices[4].clip_min.t = (bottom_clipped - bottom) * 65535 / vertical_corner_size;
	vertices[4].clip_max.s = 65535;
	vertices[4].clip_max.t = (middle_bottom_clipped - bottom) * 65535 / vertical_corner_size;
	vertices[4].position_min = {middle_left_clipped, bottom_clipped};
	vertices[4].position_max = {middle_right_clipped, middle_bottom_clipped};
	vertices[4].texture_size = {1, vertical_corner_size};
	vertices[4].in_index = {manager.button_bottom_in};
	vertices[4].out_index = {manager.button_bottom_out};

	vertices[5].border_color = settings::button::border_color;
	vertices[5].bottom_color = middle_top_color;
	vertices[5].top_color = top_color;
	vertices[5].clip_min.s = 0;
	vertices[5].clip_min.t = (middle_top_clipped - middle_top) * 65535 / vertical_corner_size;
	vertices[5].clip_max.s = 65535;
	vertices[5].clip_max.t = (top_clipped - middle_top) * 65535 / vertical_corner_size;
	vertices[5].position_min = {middle_left_clipped, middle_top_clipped};
	vertices[5].position_max = {middle_right_clipped, top_clipped};
	vertices[5].texture_size = {1, vertical_corner_size};
	vertices[5].in_index = {manager.button_top_in};
	vertices[5].out_index = {manager.button_top_out};

	vertices[6].border_color = settings::button::border_color;
	vertices[6].bottom_color = middle_bottom_color;
	vertices[6].top_color = middle_top_color;
	vertices[6].clip_min.s = (left_clipped - left) * 65535 / horizontal_corner_size;
	vertices[6].clip_min.t = 0;
	vertices[6].clip_max.s = (middle_left_clipped - left) * 65535 / horizontal_corner_size;
	vertices[6].clip_max.t = 65535;
	vertices[6].position_min = {left_clipped, middle_bottom_clipped};
	vertices[6].position_max = {middle_left_clipped, middle_top_clipped};
	vertices[6].texture_size = {horizontal_corner_size, 1};
	vertices[6].in_index = {manager.button_left_in};
	vertices[6].out_index = {manager.button_left_out};

	vertices[7].border_color = settings::button::border_color;
	vertices[7].bottom_color = middle_bottom_color;
	vertices[7].top_color = middle_top_color;
	vertices[7].clip_min.s = (middle_right_clipped - middle_right) * 65535 / horizontal_corner_size;
	vertices[7].clip_min.t = 0;
	vertices[7].clip_max.s = (right_clipped - middle_right) * 65535 / horizontal_corner_size;
	vertices[7].clip_max.t = 65535;
	vertices[7].position_min = {middle_right_clipped, middle_bottom_clipped};
	vertices[7].position_max = {right_clipped, middle_top_clipped};
	vertices[7].texture_size = {horizontal_corner_size, 1};
	vertices[7].in_index = {manager.button_right_in};
	vertices[7].out_index = {manager.button_right_out};

	vertices[8].border_color = settings::button::border_color;
	vertices[8].bottom_color = middle_bottom_color;
	vertices[8].top_color = middle_top_color;
	vertices[8].clip_min = {0, 0};
	vertices[8].clip_max = {65535, 65535};
	vertices[8].position_min = {middle_left_clipped, middle_bottom_clipped};
	vertices[8].position_max = {middle_right_clipped, middle_top_clipped};
	vertices[8].texture_size = {1, 1};
	vertices[8].in_index = {manager.button_center_in};
	vertices[8].out_index = {manager.button_center_out};
}

ui::Dip Button::GetLeft() const
{
	return left_;
}

ui::Dip Button::GetBottom() const
{
	return bottom_;
}

ui::Dip Button::GetRight() const
{
	return right_;
}

ui::Dip Button::GetTop() const
{
	return top_;
}

ui::Dip Button::GetClipLeft() const
{
	return clip_left_;
}

ui::Dip Button::GetClipRight() const
{
	return clip_right_;
}

ui::Dip Button::GetClipBottom() const
{
	return clip_bottom_;
}

ui::Dip Button::GetClipTop() const
{
	return clip_top_;
}

ui::Dip Button::GetBaseWidth(ui::Dip width) const
{
	return width + settings::button::base_width_margin;
}

ui::Dip Button::GetBaseHeight(ui::Dip height) const
{
	return height + settings::button::base_height_margin;
}

}
}
