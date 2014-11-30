#pragma once

#include "button.hxx"

#include "drawable.hpp"
#include "ui/unit.hxx"
#include "ui/window_base.hxx"
#include "vertex/outline_gradient.hxx"

#include <cstdint>

namespace twil {
namespace theme {

/// \brief Responsible for drawing a button.
class Button
:
	public Drawable<vertex::OutlineGradient>
{
	Button(Button const &) = delete;
	Button & operator =(Button const &) = delete;

private:
	ui::WindowBase * window_;
	ui::Dip left_ = 0;
	ui::Dip bottom_ = 0;
	ui::Dip right_ = 0.0f;
	ui::Dip top_ = 0.0f;
	ui::Dip clip_left_ = 0.0f;
	ui::Dip clip_bottom_ = 0.0f;
	ui::Dip clip_right_ = 0.0f;
	ui::Dip clip_top_ = 0.0f;
	bool is_down_ = false;

public:
	Button() = default;
	void Init(ui::WindowBase &);

	/// \brief Sets whether the button is up or down.
	void SetIsDown(bool is_down);

	/// \returns The left margin for the theme.
	ui::Dip GetLeftMargin() const;

	/// \returns The right margin for the theme.
	ui::Dip GetRightMargin() const;

	/// \returns The bottom margin for the theme.
	ui::Dip GetBottomMargin() const;

	/// \returns The top margin for the theme.
	ui::Dip GetTopMargin() const;

	// Drawable
	void Draw(vertex::OutlineGradient *) const final;

	// Widget
	void MoveX(ui::Dip);
	void MoveY(ui::Dip);

	void ResizeWidth(ui::Dip);
	void ResizeHeight(ui::Dip);

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

	ui::Dip GetBaseWidth(ui::Dip) const;
	ui::Dip GetBaseHeight(ui::Dip) const;
};

}
}
