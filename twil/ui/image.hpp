#pragma once

#include "image.hxx"

#include "container.hpp"
#include "mouse_handler.hpp"
#include "window_base.hpp"
#include "theme/image.hpp"

#include <string>

namespace twil {
namespace ui {

/// \brief A Widget that draws an image on the screen.
/// \param Layout A layout class used for positioning and clipping.
template<typename Layout>
class Image
:
	public MouseHandler
{
	Image(Image const &) = delete;
	Image & operator =(Image const &) = delete;

private:
	Container * parent_;
	WindowBase * window_;
	Layout layout_;
	theme::Image theme_image_;
	std::u32string text_;

	void LayoutX()
	{
		Dip delta = layout_.GetLayoutLeft(GetBaseWidth()) - theme_image_.GetLeft();
		theme_image_.MoveX(delta);
		theme_image_.SetClipLeft(layout_.GetLayoutClipLeft());
		theme_image_.SetClipRight(layout_.GetLayoutClipRight());
	}

	void LayoutY()
	{
		Dip delta = layout_.GetLayoutBottom(GetBaseHeight()) - theme_image_.GetBottom();
		theme_image_.MoveY(delta);
		theme_image_.SetClipBottom(layout_.GetLayoutClipBottom());
		theme_image_.SetClipTop(layout_.GetLayoutClipTop());
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
	// Image
	Image() = default;

	void Init(Container & parent, WindowBase  & window)
	{
		parent_ = &parent;
		window_ = &window;
		theme_image_.Init(window);
	}

	/// \brief Set the bitmap that the Image displays.
	void SetImage(char const * path)
	{
		theme_image_.SetImage(path);
		LayoutX();
		LayoutY();
		parent_->HandleChildBaseWidthChanged(this);
		parent_->HandleChildBaseHeightChanged(this);
	}

	// Widget
	void MoveX(Dip x)
	{
		layout_.MoveX(x);
		theme_image_.MoveX(x);
	}

	void MoveY(Dip y)
	{
		layout_.MoveY(y);
		theme_image_.MoveY(y);
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
		theme_image_.SetClipLeft(layout_.GetLayoutClipLeft());
	}

	void SetClipRight(Dip x)
	{
		layout_.SetClipRight(x);
		theme_image_.SetClipRight(layout_.GetLayoutClipRight());
	}

	void SetClipBottom(Dip y)
	{
		layout_.SetClipBottom(y);
		theme_image_.SetClipBottom(layout_.GetLayoutClipBottom());
	}

	void SetClipTop(Dip y)
	{
		layout_.SetClipTop(y);
		theme_image_.SetClipTop(layout_.GetLayoutClipTop());
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
		return theme_image_.GetBaseWidth();
	}

	Dip GetBaseHeight() const
	{
		return theme_image_.GetBaseHeight();
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
