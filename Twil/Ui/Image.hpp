#pragma once

#include "ImageFwd.hpp"

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Theme/Image.hpp"

#include <string>

namespace Twil {
namespace Ui {

/// \brief A Widget that draws an image on the screen.
/// \param LayoutT A layout class used for positioning and clipping.
template<typename LayoutT>
class ImageT
:
	public MouseHandlerT
{
	ImageT(ImageT const &) = delete;
	ImageT & operator =(ImageT const &) = delete;

private:
	ContainerT * mParent;
	WindowBaseT * mWindow;
	LayoutT mLayout;
	Theme::ImageT mThemeImage;
	std::u32string mText;

	void layoutX()
	{
		DipT Delta = mLayout.getLayoutLeft(getBaseWidth()) - mThemeImage.getLeft();
		mThemeImage.moveX(Delta);
		mThemeImage.setClipLeft(mLayout.getLayoutClipLeft());
		mThemeImage.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		DipT Delta = mLayout.getLayoutBottom(getBaseHeight()) - mThemeImage.getBottom();
		mThemeImage.moveY(Delta);
		mThemeImage.setClipBottom(mLayout.getLayoutClipBottom());
		mThemeImage.setClipTop(mLayout.getLayoutClipTop());
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
	// Image
	ImageT() = default;

	void init(ContainerT & Parent, WindowBaseT  & Window)
	{
		mParent = &Parent;
		mWindow = &Window;
		mThemeImage.init(Window);
	}

	/// \brief Set the bitmap that the Image displays.
	void setImage(char const * Path)
	{
		mThemeImage.setImage(Path);
		layoutX();
		layoutY();
		mParent->handleChildBaseWidthChanged(this);
		mParent->handleChildBaseHeightChanged(this);
	}

	// Widget
	void moveX(DipT X)
	{
		mLayout.moveX(X);
		mThemeImage.moveX(X);
	}

	void moveY(DipT Y)
	{
		mLayout.moveY(Y);
		mThemeImage.moveY(Y);
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
		mThemeImage.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(DipT X)
	{
		mLayout.setClipRight(X);
		mThemeImage.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(DipT Y)
	{
		mLayout.setClipBottom(Y);
		mThemeImage.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(DipT Y)
	{
		mLayout.setClipTop(Y);
		mThemeImage.setClipTop(mLayout.getLayoutClipTop());
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
		return mThemeImage.getBaseWidth();
	}

	DipT getBaseHeight() const
	{
		return mThemeImage.getBaseHeight();
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
