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
		float Delta = mLayout.getLayoutLeft(getBaseWidth()) - mThemeImage.getLeft();
		mThemeImage.moveX(Delta);
		mThemeImage.setClipLeft(mLayout.getLayoutClipLeft());
		mThemeImage.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		float Delta = mLayout.getLayoutBottom(getBaseHeight()) - mThemeImage.getBottom();
		mThemeImage.moveY(Delta);
		mThemeImage.setClipBottom(mLayout.getLayoutClipBottom());
		mThemeImage.setClipTop(mLayout.getLayoutClipTop());
	}

	bool checkThisContains(float X, float Y)
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
	void moveX(float X)
	{
		mLayout.moveX(X);
		mThemeImage.moveX(X);
	}

	void moveY(float Y)
	{
		mLayout.moveY(Y);
		mThemeImage.moveY(Y);
	}

	void resizeWidth(float X)
	{
		mLayout.resizeWidth(X);
		layoutX();
	}

	void resizeHeight(float Y)
	{
		mLayout.resizeHeight(Y);
		layoutY();
	}

	void setClipLeft(float X)
	{
		mLayout.setClipLeft(X);
		mThemeImage.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(float X)
	{
		mLayout.setClipRight(X);
		mThemeImage.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(float Y)
	{
		mLayout.setClipBottom(Y);
		mThemeImage.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(float Y)
	{
		mLayout.setClipTop(Y);
		mThemeImage.setClipTop(mLayout.getLayoutClipTop());
	}

	float getLeft() const
	{
		return mLayout.getLeft();
	}

	float getBottom() const
	{
		return mLayout.getBottom();
	}

	float getRight() const
	{
		return mLayout.getRight();
	}

	float getTop() const
	{
		return mLayout.getTop();
	}

	float getClipLeft() const
	{
		return mLayout.getClipLeft();
	}

	float getClipBottom() const
	{
		return mLayout.getClipBottom();
	}

	float getClipRight() const
	{
		return mLayout.getClipRight();
	}

	float getClipTop() const
	{
		return mLayout.getClipTop();
	}

	float getBaseWidth() const
	{
		return mThemeImage.getBaseWidth();
	}

	float getBaseHeight() const
	{
		return mThemeImage.getBaseHeight();
	}

	void delegateMouse(float, float)
	{
		mWindow->setMouseHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(float X, float Y) final
	{
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
