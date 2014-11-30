#pragma once

#include "label.hxx"

#include "container.hpp"
#include "mouse_handler.hpp"
#include "window_base.hpp"
#include "theme/label.hpp"

#include <string>

namespace twil {
namespace ui {

/// \brief A Widget that draws text on the screen.
/// \param Layout A layout class used for positioning and clipping.
template<typename Layout>
class Label
:
	public MouseHandler
{
	Label(Label const &) = delete;
	Label & operator =(Label const &) = delete;

private:
	Container * parent_;
	WindowBase * window_;
	Layout layout_;
	theme::Label theme_label_;
	std::u32string text_;

private:
	void LayoutX()
	{
		Dip delta = layout_.GetLayoutLeft(GetBaseWidth()) - theme_label_.GetLeft();
		theme_label_.MoveX(delta);
		theme_label_.SetClipLeft(layout_.GetLayoutClipLeft());
		theme_label_.SetClipRight(layout_.GetLayoutClipRight());
	}

	void LayoutY()
	{
		Dip delta = layout_.GetLayoutBottom(GetBaseHeight()) - theme_label_.GetBottom();
		theme_label_.MoveY(delta);
		theme_label_.SetClipBottom(layout_.GetLayoutClipBottom());
		theme_label_.SetClipTop(layout_.GetLayoutClipTop());
	}

	bool CheckThisContains(Dip x, Dip y)
	{
		return (
			x >= GetLeft() && x >= GetClipLeft() &&
			x <= GetRight() && x <= GetClipRight() &&
			y >= GetBottom() && y >= GetClipBottom() &&
			y <= GetTop() && y <= GetClipTop());
	}

public:
	// Label
	Label() = default;

	void Init(Container & parent, WindowBase & window)
	{
		parent_ = &parent;
		window_ = &window;
		theme_label_.Init(window);
	}

	/// \brief Set the text that the label displays.
	void SetText(std::u32string const & text)
	{
		text_ = text;
		theme_label_.SetText(text);
		LayoutX();
		parent_->HandleChildBaseWidthChanged(this);
	}

	// Widget
	void MoveX(Dip x)
	{
		layout_.MoveX(x);
		theme_label_.MoveX(x);
	}

	void MoveY(Dip y)
	{
		layout_.MoveY(y);
		theme_label_.MoveY(y);
	}

	void ResizeWidth(Dip x)
	{
		layout_.ResizeWidth(x);
		LayoutX();
	}

	void ResizeHeight(Dip y)
	{
		layout_.ResizeHeight(y);
		LayoutY();
	}

	void SetClipLeft(Dip x)
	{
		layout_.SetClipLeft(x);
		theme_label_.SetClipLeft(layout_.GetLayoutClipLeft());
	}

	void SetClipRight(Dip x)
	{
		layout_.SetClipRight(x);
		theme_label_.SetClipRight(layout_.GetLayoutClipRight());
	}

	void SetClipBottom(Dip y)
	{
		layout_.SetClipBottom(y);
		theme_label_.SetClipBottom(layout_.GetLayoutClipBottom());
	}

	void SetClipTop(Dip y)
	{
		layout_.SetClipTop(y);
		theme_label_.SetClipTop(layout_.GetLayoutClipTop());
	}

	Dip GetLeft() const
	{
		return layout_.GetLeft();
	}

	Dip GetBottom() const
	{
		return layout_.GetBottom();
	}

	Dip GetRight() const
	{
		return layout_.GetRight();
	}

	Dip GetTop() const
	{
		return layout_.GetTop();
	}

	Dip GetClipLeft() const
	{
		return layout_.GetClipLeft();
	}

	Dip GetClipBottom() const
	{
		return layout_.GetClipBottom();
	}

	Dip GetClipRight() const
	{
		return layout_.GetClipRight();
	}

	Dip GetClipTop() const
	{
		return layout_.GetClipTop();
	}

	Dip GetBaseWidth() const
	{
		return theme_label_.GetBaseWidth();
	}

	Dip GetBaseHeight() const
	{
		return theme_label_.GetBaseHeight();
	}

	void DelegateMouse(Dip, Dip)
	{
		window_->SetMouseHandler(*this);
	}

	// MouseHandler
	void HandleMouseMotion(Dip x, Dip y) final
	{
		if (!CheckThisContains(x, y)) parent_->ReleaseMouse(x, y);
	}
};

}
}
