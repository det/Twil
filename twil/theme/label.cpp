#include "label.hpp"

#include "ui/window_base.hpp"

namespace twil {
namespace theme {

void Label::Init(ui::WindowBase & window)
{
	window_ = &window;
	auto & manager = window_->GetThemeManager();
	manager.solid_array_.Allocate(*this, 0);
	height_ = manager.label_size_.GetHeight() / 64;
}

void Label::SetText(std::u32string const & text)
{
	auto & manager = window_->GetThemeManager();

	glyphs_.clear();
	auto & face = manager.label_face_;
	face.SetActiveSize(manager.label_size_);

	FT_Vector pen{0, -manager.label_size_.GetDescender()};
	GlyphEntry previous_entry{};

	for (auto codepoint : text)
	{
		auto entry = manager.LoadGlyphEntry(face, codepoint);

		// We can hit a divide by 0 in clipping without this check
		if (entry.width == 0 || entry.height == 0) continue;

		// Apply characacter pair kerning / Hint advance adjustment
		auto delta = face.GetKerning(previous_entry.index, entry.index);
		if (previous_entry.rsb_delta - entry.lsb_delta >= 32) delta.x -= 64;
		else if (previous_entry.rsb_delta - entry.lsb_delta < -32) delta.x += 64;
		pen.x += delta.x;
		pen.y += delta.y;

		ui::Pixel left = (pen.x + entry.bearings.x) / 64;
		ui::Pixel bottom = (pen.y + entry.bearings.y) / 64;
		ui::Pixel right = left + entry.width;
		ui::Pixel top = bottom + entry.height;

		LabelGlyph glyph;
		glyph.position_min = {left, bottom};
		glyph.position_max = {right, top};
		glyph.texture_size = {entry.width, entry.height};
		glyph.offset = {entry.offset};
		glyphs_.push_back(glyph);

		pen.x += entry.advance.x;
		pen.y += entry.advance.y;

		previous_entry = entry;
	}

	width_ = pen.x / 64;
	manager.solid_array_.Resize(*this, glyphs_.size());
	manager.solid_array_.MarkNeedsRedraw(*this);
}

void Label::SetClipLeft(ui::Dip x)
{
	clip_left_ = x;
	window_->GetThemeManager().solid_array_.MarkNeedsRedraw(*this);
}

void Label::SetClipRight(ui::Dip x)
{
	clip_right_ = x;
	window_->GetThemeManager().solid_array_.MarkNeedsRedraw(*this);
}

void Label::SetClipBottom(ui::Dip y)
{
	clip_bottom_ = y;
	window_->GetThemeManager().solid_array_.MarkNeedsRedraw(*this);
}

void Label::SetClipTop(ui::Dip y)
{
	clip_top_ = y;
	window_->GetThemeManager().solid_array_.MarkNeedsRedraw(*this);
}

void Label::Draw(vertex::FillSolid * vertices) const
{
	ui::Pixel left = window_->ConvertDipToPixelX(left_);
	ui::Pixel bottom = window_->ConvertDipToPixelY(bottom_);

	for (std::size_t i = 0, e = glyphs_.size(); i != e; ++i)
	{
		ui::Pixel glyph_left = left + glyphs_[i].position_min.x;
		ui::Pixel glyph_right = left + glyphs_[i].position_max.x;
		ui::Pixel glyph_bottom = bottom + glyphs_[i].position_min.y;
		ui::Pixel glyph_top = bottom + glyphs_[i].position_max.y;

		ui::Pixel clip_left = window_->ConvertDipToPixelX(clip_left_);
		ui::Pixel clip_right = window_->ConvertDipToPixelX(clip_right_);
		ui::Pixel clip_bottom = window_->ConvertDipToPixelY(clip_bottom_);
		ui::Pixel clip_top = window_->ConvertDipToPixelY(clip_top_);

		ui::Pixel width = glyph_right - glyph_left;
		ui::Pixel height = glyph_top - glyph_bottom;

		ui::Pixel left_clipped = glyph_left;
		ui::Pixel right_clipped = glyph_right;
		ui::Pixel bottom_clipped = glyph_bottom;
		ui::Pixel top_clipped = glyph_top;

		left_clipped = std::max(left_clipped, clip_left);
		right_clipped = std::max(right_clipped, clip_left);
		left_clipped = std::min(left_clipped, clip_right);
		right_clipped = std::min(right_clipped, clip_right);
		bottom_clipped = std::max(bottom_clipped, clip_bottom);
		top_clipped = std::max(top_clipped, clip_bottom);
		bottom_clipped = std::min(bottom_clipped, clip_top);
		top_clipped = std::min(top_clipped, clip_top);

		vertices[i].color = {0, 0, 0, 255};
		vertices[i].clip_min.s = (left_clipped - glyph_left) * 65535 / width;
		vertices[i].clip_min.t = (bottom_clipped - glyph_bottom) * 65535 / height;
		vertices[i].clip_max.s = (right_clipped - glyph_left) * 65535 / width;
		vertices[i].clip_max.t = (top_clipped - glyph_bottom) * 65535 / height;
		vertices[i].position_min = {left_clipped, bottom_clipped};
		vertices[i].position_max = {right_clipped, top_clipped};
		vertices[i].texture_size = glyphs_[i].texture_size;
		vertices[i].offset = glyphs_[i].offset;
	}
}

void Label::MoveX(ui::Dip x)
{
	left_ += x;
	clip_left_ += x;
	clip_right_ += x;
	window_->GetThemeManager().solid_array_.MarkNeedsRedraw(*this);
}

void Label::MoveY(ui::Dip y)
{
	bottom_ += y;
	clip_bottom_ += y;
	clip_top_ += y;
	window_->GetThemeManager().solid_array_.MarkNeedsRedraw(*this);
}

ui::Dip Label::GetLeft() const
{
	return left_;
}

ui::Dip Label::GetBottom() const
{
	return bottom_;
}

ui::Dip Label::GetRight() const
{
	return left_ + GetBaseWidth();
}

ui::Dip Label::GetTop() const
{
	return bottom_ + GetBaseHeight();
}

ui::Dip Label::GetClipLeft() const
{
	return clip_left_;
}

ui::Dip Label::GetClipRight() const
{
	return clip_right_;
}

ui::Dip Label::GetClipBottom() const
{
	return clip_bottom_;
}

ui::Dip Label::GetClipTop() const
{
	return clip_top_;
}

ui::Dip Label::GetBaseWidth() const
{
	return window_->ConvertPixelToDipX(width_);
}

ui::Dip Label::GetBaseHeight() const
{
	return window_->ConvertPixelToDipY(height_);
}

}
}
