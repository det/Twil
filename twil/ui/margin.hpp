#pragma once

#include "margin.hxx"

#include "container.hpp"
#include "mouse_handler.hpp"
#include "window_base.hpp"

namespace twil {
namespace ui {

/// \brief Provides a fixed size margin around a child
///
/// \param space_x Size of the left and right margins.
/// \param space_y Size of the bottom and top margins.
/// \param T Type of the child widget.
template<Dip space_x, Dip space_y, typename T>
class Margin
:
	public Container,
	public MouseHandler
{
	Margin(Margin const &) = delete;
	Margin & operator =(Margin const &) = delete;

private:
	Container * parent_;
	WindowBase * window_;
	T child_;

	bool CheckThisContains(Dip x, Dip y)
	{
		return (
			x >= GetLeft() && x >= GetClipLeft() &&
			x <= GetRight() && x <= GetClipRight() &&
			y >= GetBottom() && y >= GetClipBottom() &&
			y <= GetTop() && y <= GetClipTop());
	}

	bool CheckChildContains(Dip x, Dip y)
	{
		return (
			x >= child_.GetLeft() && x <= child_.GetRight() &&
			y >= child_.GetBottom() && y <= child_.GetTop());
	}

public:
	// Margin
	Margin() = default;

	void Init(Container & parent, WindowBase & window)
	{
		parent_ = &parent;
		window_ = &window;

		child_.Init(*this, window);
		child_.MoveX(space_x);
		child_.MoveY(space_y);
		child_.ResizeWidth(-space_x * 2);
		child_.ResizeHeight(-space_y * 2);
	}

	/// \returns a reference to the child widget
	T & GetChild()
	{
		return child_;
	}

	/// \returns a const reference to the child widget
	T const & GetChild() const
	{
		return child_;
	}

	// Widget
	void MoveX(Dip x)
	{
		child_.MoveX(x);
	}

	void MoveY(Dip y)
	{
		child_.MoveY(y);
	}

	void ResizeWidth(Dip x)
	{
		child_.ResizeWidth(x);
	}

	void ResizeHeight(Dip y)
	{
		child_.ResizeHeight(y);
	}

	void SetClipLeft(Dip x)
	{
		child_.SetClipLeft(x);
	}

	void SetClipRight(Dip x)
	{
		child_.SetClipRight(x);
	}

	void SetClipBottom(Dip y)
	{
		child_.SetClipBottom(y);
	}

	void SetClipTop(Dip y)
	{
		child_.SetClipTop(y);
	}

	Dip GetLeft() const
	{
		return child_.GetLeft() - space_x;
	}

	Dip GetBottom() const
	{
		return child_.GetBottom() - space_y;
	}

	Dip GetRight() const
	{
		return child_.GetRight() + space_y;
	}

	Dip GetTop() const
	{
		return child_.GetTop() + space_y;
	}

	Dip GetClipLeft() const
	{
		return child_.GetClipLeft();
	}

	Dip GetClipBottom() const
	{
		return child_.GetClipBottom();
	}

	Dip GetClipRight() const
	{
		return child_.GetClipRight();
	}

	Dip GetClipTop() const
	{
		return child_.GetClipTop();
	}

	Dip GetBaseWidth() const
	{
		return child_.GetBaseWidth() + space_x + space_x;
	}

	Dip GetBaseHeight() const
	{
		return child_.GetBaseHeight() + space_y + space_y;
	}

	void DelegateMouse(Dip x, Dip y)
	{
		if (CheckChildContains(x, y)) child_.DelegateMouse(x, y);
		else window_->SetMouseHandler(*this);
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
		if (CheckThisContains(x, y)) window_->SetMouseHandler(*this);
		else parent_->ReleaseMouse(x, y);
	}

	// MouseHandler
	void HandleMouseMotion(Dip x, Dip y) final
	{
		if (CheckChildContains(x, y)) child_.DelegateMouse(x, y);
		if (!CheckThisContains(x, y)) parent_->ReleaseMouse(x, y);
	}
};

}
}
