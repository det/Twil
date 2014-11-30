#pragma once

#include "label.hxx"

#include "drawable.hpp"
#include "ui/unit.hxx"
#include "ui/window_base.hxx"
#include "vertex/fill_solid.hpp"

#include <string>
#include <vector>

namespace twil {
namespace theme {

struct LabelGlyph
{
	attribute::Position2H position_min;
	attribute::Position2H position_max;
	attribute::Size2H texture_size;
	attribute::Offset1I offset;
};

/// \brief Responsible for drawing a label.
class Label
:
	Drawable<vertex::FillSolid>
{
	Label(Label const &) = delete;
	Label & operator =(Label const &) = delete;

private:
	ui::WindowBase * window_;
	std::vector<LabelGlyph> glyphs_;
	ui::Pixel width_ = 0;
	ui::Pixel height_ = 0;
	ui::Dip left_ = 0.0f;
	ui::Dip bottom_ = 0.0f;
	ui::Dip clip_left_ = 0.0f;
	ui::Dip clip_bottom_ = 0.0f;
	ui::Dip clip_right_ = 0.0f;
	ui::Dip clip_top_ = 0.0f;

public:
	Label() = default;
	void Init(ui::WindowBase & window);

	/// \brief Sets the text to display.
	void SetText(std::u32string const & text);

	// Drawable
	void Draw(vertex::FillSolid *) const final;

	// Widget
	void MoveX(ui::Dip);
	void MoveY(ui::Dip);

	void SetClipLeft(ui::Dip);
	void SetClipBottom(ui::Dip);
	void SetClipRight(ui::Dip);
	void SetClipTop(ui::Dip);

	ui::Dip GetLeft() const;
	ui::Dip GetBottom() const;
	ui::Dip GetRight() const;
	ui::Dip GetTop() const;

	ui::Dip GetClipLeft() const;
	ui::Dip GetClipRight() const;
	ui::Dip GetClipBottom() const;
	ui::Dip GetClipTop() const;

	ui::Dip GetBaseWidth() const;
	ui::Dip GetBaseHeight() const;
};

}
}
