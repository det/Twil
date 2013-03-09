#pragma once

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Theme/Image.hpp"

#include <string>

namespace Twil {

namespace Theme {
class ManagerT;
}

namespace Ui {

/// \brief A Widget that draws an image on the screen.
/// \param LayoutT A layout class used for positioning and clipping.
template<typename LayoutT>
class ImageT :
	public MouseHandlerT
{
	private:
	ContainerT * mParent;
	WindowBaseT * mWindow;
	LayoutT mLayout;
	Theme::ImageT mTheme;
	std::u32string mText;

	private:
	void layoutX()
	{
		signed short Delta = mLayout.getLayoutLeft(getBaseWidth()) - mTheme.getLeft();
		mTheme.moveX(Delta);
		mTheme.setClipLeft(mLayout.getLayoutClipLeft());
		mTheme.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		signed short Delta = mLayout.getLayoutBottom(getBaseHeight()) - mTheme.getBottom();
		mTheme.moveY(Delta);
		mTheme.setClipBottom(mLayout.getLayoutClipBottom());
		mTheme.setClipTop(mLayout.getLayoutClipTop());
	}

	bool checkThisContains(signed short X, signed short Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop()
		);
	}

	public:
	// Image
	void init(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Manager)
	{
		mParent = &Parent;
		mWindow = &Window;
		mTheme.init(Manager);
	}

	/// \brief Set the bitmap that the Image displays.
	void setImage(char const * Path)
	{
		mTheme.setImage(Path);
		mWindow->markNeedsDraw();
		layoutX();
		layoutY();
		mParent->handleChildBaseWidthChanged(this);
		mParent->handleChildBaseHeightChanged(this);
	}

	// Widget
	void moveX(signed short X)
	{
		mLayout.moveX(X);
		mTheme.moveX(X);
	}

	void moveY(signed short Y)
	{
		mLayout.moveY(Y);
		mTheme.moveY(Y);
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
		mTheme.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(signed short X)
	{
		mLayout.setClipRight(X);
		mTheme.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(signed short Y)
	{
		mLayout.setClipBottom(Y);
		mTheme.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(signed short Y)
	{
		mLayout.setClipTop(Y);
		mTheme.setClipTop(mLayout.getLayoutClipTop());
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
		return mTheme.getBaseWidth();
	}

	signed short getBaseHeight() const
	{
		return mTheme.getBaseHeight();
	}

	void delegateMouse(signed short, signed short)
	{
		mWindow->setMouseHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
