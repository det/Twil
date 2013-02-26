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
class LabelT :
	public MouseHandlerT
{
	private:
	ContainerT & mParent;
	WindowBaseT & mWindow;
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
		return X >= getLeft() && X <= getRight() && Y >= getBottom() && Y <= getTop();
	}

	public:
	// Label
	LabelT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mWindow(Window), // Gcc bug prevents brace initialization syntax here
		mThemeLabel{Theme}
	{}

	/// \brief Set the text that the label displays.
	void setText(std::u32string const & Text)
	{
		mText = Text;
		mThemeLabel.setText(Text);
		mWindow.markNeedsDraw();
		layoutX();
		mParent.handleChildBaseWidthChanged(this);
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
		mWindow.setMouseHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (!checkThisContains(X, Y)) mParent.releaseMouse(X, Y);
	}
};

}
}
