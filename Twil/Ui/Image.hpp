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
		std::int16_t Delta = mLayout.getLayoutLeft(getBaseWidth()) - mThemeImage.getLeft();
		mThemeImage.moveX(Delta);
		mThemeImage.setClipLeft(mLayout.getLayoutClipLeft());
		mThemeImage.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		std::int16_t Delta = mLayout.getLayoutBottom(getBaseHeight()) - mThemeImage.getBottom();
		mThemeImage.moveY(Delta);
		mThemeImage.setClipBottom(mLayout.getLayoutClipBottom());
		mThemeImage.setClipTop(mLayout.getLayoutClipTop());
	}

	bool checkThisContains(std::int16_t X, std::int16_t Y)
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

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		mWindow = &Window;
		mThemeImage.init(Window.getThemeManager());
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
	void moveX(std::int16_t X)
	{
		mLayout.moveX(X);
		mThemeImage.moveX(X);
	}

	void moveY(std::int16_t Y)
	{
		mLayout.moveY(Y);
		mThemeImage.moveY(Y);
	}

	void resizeWidth(std::int16_t X)
	{
		mLayout.resizeWidth(X);
		layoutX();
	}

	void resizeHeight(std::int16_t Y)
	{
		mLayout.resizeHeight(Y);
		layoutY();
	}

	void setClipLeft(std::int16_t X)
	{
		mLayout.setClipLeft(X);
		mThemeImage.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(std::int16_t X)
	{
		mLayout.setClipRight(X);
		mThemeImage.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(std::int16_t Y)
	{
		mLayout.setClipBottom(Y);
		mThemeImage.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(std::int16_t Y)
	{
		mLayout.setClipTop(Y);
		mThemeImage.setClipTop(mLayout.getLayoutClipTop());
	}

	std::int16_t getLeft() const
	{
		return mLayout.getLeft();
	}

	std::int16_t getBottom() const
	{
		return mLayout.getBottom();
	}

	std::int16_t getRight() const
	{
		return mLayout.getRight();
	}

	std::int16_t getTop() const
	{
		return mLayout.getTop();
	}

	std::int16_t getClipLeft() const
	{
		return mLayout.getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return mLayout.getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return mLayout.getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return mLayout.getClipTop();
	}

	std::int16_t getBaseWidth() const
	{
		return mThemeImage.getBaseWidth();
	}

	std::int16_t getBaseHeight() const
	{
		return mThemeImage.getBaseHeight();
	}

	void delegateMouse(std::int16_t, std::int16_t)
	{
		mWindow->getMouseManager().setHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(std::int16_t X, std::int16_t Y) final
	{
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
