#pragma once

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Theme/Label.hpp"

#include <string>

namespace Twil {

namespace Theme {
class ManagerT;
}

namespace Ui {

/// \brief A Widget that draws text on the screen.
/// \param LayoutT A layout class used for positioning and clipping.
template<typename LayoutT>
class LabelT
:
	public MouseHandlerT
{
	LabelT(LabelT const &) = delete;
	LabelT & operator =(LabelT const &) = delete;

	private:
	ContainerT * mParent;
	WindowBaseT * mWindow;
	LayoutT mLayout;
	Theme::LabelT mThemeLabel;
	std::u32string mText;

	private:
	void layoutX()
	{
		signed short Delta = mLayout.getLayoutLeft(getBaseWidth()) - mThemeLabel.getLeft();
		mThemeLabel.moveX(Delta);
		mThemeLabel.setClipLeft(mLayout.getLayoutClipLeft());
		mThemeLabel.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		signed short Delta = mLayout.getLayoutBottom(getBaseHeight()) - mThemeLabel.getBottom();
		mThemeLabel.moveY(Delta);
		mThemeLabel.setClipBottom(mLayout.getLayoutClipBottom());
		mThemeLabel.setClipTop(mLayout.getLayoutClipTop());
	}

	bool checkThisContains(signed short X, signed short Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

	public:
	// Label
	LabelT() = default;

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		mWindow = &Window;
		mThemeLabel.init(Window.getThemeManager());
	}

	/// \brief Set the text that the label displays.
	void setText(std::u32string const & Text)
	{
		mText = Text;
		mThemeLabel.setText(Text);
		layoutX();
		mParent->handleChildBaseWidthChanged(this);
	}

	// Widget
	void moveX(signed short X)
	{
		mLayout.moveX(X);
		mThemeLabel.moveX(X);
	}

	void moveY(signed short Y)
	{
		mLayout.moveY(Y);
		mThemeLabel.moveY(Y);
	}

	void resizeWidth(signed short X)
	{
		mLayout.resizeWidth(X);
		layoutX();
	}

	void resizeHeight(signed short Y)
	{
		mLayout.resizeHeight(Y);
		layoutY();
	}

	void setClipLeft(signed short X)
	{
		mLayout.setClipLeft(X);
		mThemeLabel.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(signed short X)
	{
		mLayout.setClipRight(X);
		mThemeLabel.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(signed short Y)
	{
		mLayout.setClipBottom(Y);
		mThemeLabel.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(signed short Y)
	{
		mLayout.setClipTop(Y);
		mThemeLabel.setClipTop(mLayout.getLayoutClipTop());
	}

	signed short getLeft() const
	{
		return mLayout.getLeft();
	}

	signed short getBottom() const
	{
		return mLayout.getBottom();
	}

	signed short getRight() const
	{
		return mLayout.getRight();
	}

	signed short getTop() const
	{
		return mLayout.getTop();
	}

	signed short getClipLeft() const
	{
		return mLayout.getClipLeft();
	}

	signed short getClipBottom() const
	{
		return mLayout.getClipBottom();
	}

	signed short getClipRight() const
	{
		return mLayout.getClipRight();
	}

	signed short getClipTop() const
	{
		return mLayout.getClipTop();
	}

	signed short getBaseWidth() const
	{
		return mThemeLabel.getBaseWidth();
	}

	signed short getBaseHeight() const
	{
		return mThemeLabel.getBaseHeight();
	}

	void delegateMouse(signed short, signed short)
	{
		mWindow->getMouseManager().setHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
