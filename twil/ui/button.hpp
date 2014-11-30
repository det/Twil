#pragma once

#include "button.hxx"

#include "container.hpp"
#include "mouse_handler.hpp"
#include "data/event.hpp"
#include "window_base.hpp"
#include "theme/button.hpp"

#include <stdexcept>

namespace twil {
namespace ui {

/// \brief A Widget that can be clicked to activate an event.
/// \param T Type of the child widget.
template<typename T>
class Button
:
	public Container,
	public MouseHandler
{
	Button(Button const &) = delete;
	Button & operator =(Button const &) = delete;

private:
	Container * parent_;
	WindowBase * window_;
	theme::Button theme_button_;
	T child_;
	bool is_pressed_;
	bool has_mouse_;

	bool CheckThisContains(Dip x, Dip y)
	{
		return (
			x >= GetLeft() && x >= GetClipLeft() &&
			x <= GetRight() && x <= GetClipRight() &&
			y >= GetBottom() && y >= GetClipBottom() &&
			y <= GetTop() && y <= GetClipTop());
	}

public:
	//Button
	data::Event<> Clicked;

	Button() = default;

	void Init(Container & parent, WindowBase & window)
	{
		parent_ = &parent;
		window_ = &window;
		is_pressed_ = false;
		has_mouse_ = false;

		theme_button_.Init(window);
		child_.Init(*this, window);
		auto left_margin = theme_button_.GetLeftMargin();
		auto right_margin = theme_button_.GetRightMargin();
		auto bottom_margin = theme_button_.GetBottomMargin();
		auto top_margin = theme_button_.GetTopMargin();
		child_.MoveX(left_margin);
		child_.MoveY(bottom_margin);
		child_.ResizeWidth(-left_margin + -right_margin);
		child_.ResizeHeight(-bottom_margin + -top_margin);
	}

	/// \returns A reference to the child widget.
	T & GetChild()
	{
		return child_;
	}

	/// \returns A const reference to the child widget.
	T const & GetChild() const
	{
		return child_;
	}

	// Widget
	void MoveX(Dip x)
	{
		theme_button_.MoveX(x);
		child_.MoveX(x);
	}

	void MoveY(Dip y)
	{
		theme_button_.MoveY(y);
		child_.MoveY(y);
	}

	void ResizeWidth(Dip x)
	{
		theme_button_.ResizeWidth(x);
		child_.ResizeWidth(x);
	}

	void ResizeHeight(Dip y)
	{
		theme_button_.ResizeHeight(y);
		child_.ResizeHeight(y);
	}

	void SetClipLeft(Dip x)
	{
		theme_button_.SetClipLeft(x);
		child_.SetClipLeft(x);
	}

	void SetClipBottom(Dip y)
	{
		theme_button_.SetClipBottom(y);
		child_.SetClipBottom(y);
	}

	void SetClipRight(Dip x)
	{
		theme_button_.SetClipRight(x);
		child_.SetClipRight(x);
	}

	void SetClipTop(Dip y)
	{
		theme_button_.SetClipTop(y);
		child_.SetClipTop(y);
	}

	Dip GetLeft() const
	{
		return theme_button_.GetLeft();
	}

	Dip GetBottom() const
	{
		return theme_button_.GetBottom();
	}

	Dip GetRight() const
	{
		return theme_button_.GetRight();
	}

	Dip GetTop() const
	{
		return theme_button_.GetTop();
	}

	Dip GetClipLeft() const
	{
		return theme_button_.GetClipLeft();
	}

	Dip GetClipBottom() const
	{
		return theme_button_.GetClipBottom();
	}

	Dip GetClipRight() const
	{
		return theme_button_.GetClipRight();
	}

	Dip GetClipTop() const
	{
		return theme_button_.GetClipTop();
	}

	Dip GetBaseWidth() const
	{
		return theme_button_.GetBaseWidth(child_.GetBaseWidth());
	}

	Dip GetBaseHeight() const
	{
		return theme_button_.GetBaseHeight(child_.GetBaseHeight());
	}

	void DelegateMouse(Dip, Dip)
	{
		window_->SetMouseHandler(*this);
		has_mouse_ = true;
	}

	// Container
	void HandleChildBaseWidthChanged(void *) final
	{
		parent_->HandleChildBaseWidthChanged(this);
	}

	void HandleChildBaseHeightChanged(void *) final
	{
		parent_->HandleChildBaseHeightChanged(this);
	}

	void ReleaseMouse(Dip x, Dip y) final
	{
		parent_->ReleaseMouse(x, y);
	}

	// MouseHandler
	void HandleButtonPress(Dip, Dip, std::uint8_t index) final
	{
		if (index == 1)
		{
			is_pressed_ = true;
			theme_button_.SetIsDown(true);
		}
	}

	void HandleButtonRelease(Dip x, Dip y, std::uint8_t index) final
	{
		if (index == 1)
		{
			if (!is_pressed_) return;
			if (has_mouse_)
			{
				is_pressed_ = false;
				theme_button_.SetIsDown(false);
				Clicked();
			}
			else
			{
				is_pressed_ = false;
				parent_->ReleaseMouse(x, y);
			}
		}
	}

	void HandleMouseMotion(Dip x, Dip y) final
	{
		auto has_mouse = CheckThisContains(x, y);

		if (has_mouse_ && !has_mouse)
		{
			has_mouse_ = false;
			if (is_pressed_)	theme_button_.SetIsDown(false);
			else parent_->ReleaseMouse(x, y);
		}
		else if (!has_mouse_ && has_mouse)
		{
			has_mouse_ = true;
			if (is_pressed_)	theme_button_.SetIsDown(true);
		}
	}
};

}
}
