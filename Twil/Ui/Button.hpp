#pragma once

#include "ButtonFwd.hpp"

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "Data/Event.hpp"
#include "WindowBase.hpp"
#include "Theme/Button.hpp"

#include <stdexcept>

namespace Twil {
namespace Ui {

/// \brief A Widget that can be clicked to activate an event.
/// \param T Type of the child widget.
template<typename T>
class ButtonT
:
	public ContainerT,
	public MouseHandlerT
{
	ButtonT(ButtonT const &) = delete;
	ButtonT & operator =(ButtonT const &) = delete;

private:
	ContainerT * mParent;
	WindowBaseT * mWindow;
	Theme::ButtonT mThemeButton;
	T mChild;
	bool mIsPressed;
	bool mHasMouse;

	bool checkThisContains(DipT X, DipT Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

public:
	//Button
	Data::EventT<> Clicked;

	ButtonT() = default;

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		mWindow = &Window;
		mIsPressed = false;
		mHasMouse = false;

		mThemeButton.init(Window);
		mChild.init(*this, Window);
		auto LeftMargin = mThemeButton.getLeftMargin();
		auto RightMargin = mThemeButton.getRightMargin();
		auto BottomMargin = mThemeButton.getBottomMargin();
		auto TopMargin = mThemeButton.getTopMargin();
		mChild.moveX(LeftMargin);
		mChild.moveY(BottomMargin);
		mChild.resizeWidth(-LeftMargin + -RightMargin);
		mChild.resizeHeight(-BottomMargin + -TopMargin);
	}

	/// \returns A reference to the child widget.
	T & getChild()
	{
		return mChild;
	}

	/// \returns A const reference to the child widget.
	T const & getChild() const
	{
		return mChild;
	}

	// Widget
	void moveX(DipT X)
	{
		mThemeButton.moveX(X);
		mChild.moveX(X);
	}

	void moveY(DipT Y)
	{
		mThemeButton.moveY(Y);
		mChild.moveY(Y);
	}

	void resizeWidth(DipT X)
	{
		mThemeButton.resizeWidth(X);
		mChild.resizeWidth(X);
	}

	void resizeHeight(DipT Y)
	{
		mThemeButton.resizeHeight(Y);
		mChild.resizeHeight(Y);
	}

	void setClipLeft(DipT X)
	{
		mThemeButton.setClipLeft(X);
		mChild.setClipLeft(X);
	}

	void setClipBottom(DipT Y)
	{
		mThemeButton.setClipBottom(Y);
		mChild.setClipBottom(Y);
	}

	void setClipRight(DipT X)
	{
		mThemeButton.setClipRight(X);
		mChild.setClipRight(X);
	}

	void setClipTop(DipT Y)
	{
		mThemeButton.setClipTop(Y);
		mChild.setClipTop(Y);
	}

	DipT getLeft() const
	{
		return mThemeButton.getLeft();
	}

	DipT getBottom() const
	{
		return mThemeButton.getBottom();
	}

	DipT getRight() const
	{
		return mThemeButton.getRight();
	}

	DipT getTop() const
	{
		return mThemeButton.getTop();
	}

	DipT getClipLeft() const
	{
		return mThemeButton.getClipLeft();
	}

	DipT getClipBottom() const
	{
		return mThemeButton.getClipBottom();
	}

	DipT getClipRight() const
	{
		return mThemeButton.getClipRight();
	}

	DipT getClipTop() const
	{
		return mThemeButton.getClipTop();
	}

	DipT getBaseWidth() const
	{
		return mThemeButton.getBaseWidth(mChild.getBaseWidth());
	}

	DipT getBaseHeight() const
	{
		return mThemeButton.getBaseHeight(mChild.getBaseHeight());
	}

	void delegateMouse(DipT, DipT)
	{
		mWindow->setMouseHandler(*this);
		mHasMouse = true;
	}

	// Container
	void handleChildBaseWidthChanged(void *) final
	{
		mParent->handleChildBaseWidthChanged(this);
	}

	void handleChildBaseHeightChanged(void *) final
	{
		mParent->handleChildBaseHeightChanged(this);
	}

	void releaseMouse(DipT X, DipT Y) final
	{
		mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleButtonPress(DipT, DipT, std::uint8_t Index) final
	{
		if (Index == 1)
		{
			mIsPressed = true;
			mThemeButton.setIsDown(true);
		}
	}

	void handleButtonRelease(DipT X, DipT Y, std::uint8_t Index) final
	{
		if (Index == 1)
		{
			if (!mIsPressed) return;
			if (mHasMouse)
			{
				mIsPressed = false;
				mThemeButton.setIsDown(false);
				Clicked();
			}
			else
			{
				mIsPressed = false;
				mParent->releaseMouse(X, Y);
			}
		}
	}

	void handleMouseMotion(DipT X, DipT Y) final
	{
		auto HasMouse = checkThisContains(X, Y);

		if (mHasMouse && !HasMouse)
		{
			mHasMouse = false;
			if (mIsPressed)	mThemeButton.setIsDown(false);
			else mParent->releaseMouse(X, Y);
		}
		else if (!mHasMouse && HasMouse)
		{
			mHasMouse = true;
			if (mIsPressed)	mThemeButton.setIsDown(true);
		}
	}
};

}
}
