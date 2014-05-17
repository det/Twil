#pragma once

#include "LabelFwd.hpp"

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Theme/Label.hpp"

#include <string>

namespace Twil {
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
		DipT Delta = mLayout.getLayoutLeft(getBaseWidth()) - mThemeLabel.getLeft();
		mThemeLabel.moveX(Delta);
		mThemeLabel.setClipLeft(mLayout.getLayoutClipLeft());
		mThemeLabel.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		DipT Delta = mLayout.getLayoutBottom(getBaseHeight()) - mThemeLabel.getBottom();
		mThemeLabel.moveY(Delta);
		mThemeLabel.setClipBottom(mLayout.getLayoutClipBottom());
		mThemeLabel.setClipTop(mLayout.getLayoutClipTop());
	}

	bool checkThisContains(DipT X, DipT Y)
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
		mThemeLabel.init(Window);
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
	void moveX(DipT X)
	{
		mLayout.moveX(X);
		mThemeLabel.moveX(X);
	}

	void moveY(DipT Y)
	{
		mLayout.moveY(Y);
		mThemeLabel.moveY(Y);
	}

	void resizeWidth(DipT X)
	{
		mLayout.resizeWidth(X);
		layoutX();
	}

	void resizeHeight(DipT Y)
	{
		mLayout.resizeHeight(Y);
		layoutY();
	}

	void setClipLeft(DipT X)
	{
		mLayout.setClipLeft(X);
		mThemeLabel.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(DipT X)
	{
		mLayout.setClipRight(X);
		mThemeLabel.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(DipT Y)
	{
		mLayout.setClipBottom(Y);
		mThemeLabel.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(DipT Y)
	{
		mLayout.setClipTop(Y);
		mThemeLabel.setClipTop(mLayout.getLayoutClipTop());
	}

	DipT getLeft() const
	{
		return mLayout.getLeft();
	}

	DipT getBottom() const
	{
		return mLayout.getBottom();
	}

	DipT getRight() const
	{
		return mLayout.getRight();
	}

	DipT getTop() const
	{
		return mLayout.getTop();
	}

	DipT getClipLeft() const
	{
		return mLayout.getClipLeft();
	}

	DipT getClipBottom() const
	{
		return mLayout.getClipBottom();
	}

	DipT getClipRight() const
	{
		return mLayout.getClipRight();
	}

	DipT getClipTop() const
	{
		return mLayout.getClipTop();
	}

	DipT getBaseWidth() const
	{
		return mThemeLabel.getBaseWidth();
	}

	DipT getBaseHeight() const
	{
		return mThemeLabel.getBaseHeight();
	}

	void delegateMouse(DipT, DipT)
	{
		mWindow->setMouseHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(DipT X, DipT Y) final
	{
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
