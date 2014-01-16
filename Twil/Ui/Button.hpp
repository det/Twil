#pragma once

#include "Container.hpp"
#include "Window.hpp"
#include "Data/Event.hpp"
#include "Gl/Context.hpp"
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

	bool checkThisContains(float X, float Y)
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

		mThemeButton.init(Window.getThemeManager());
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
	void moveX(float X)
	{
		mThemeButton.moveX(X);
		mChild.moveX(X);
	}

	void moveY(float Y)
	{
		mThemeButton.moveY(Y);
		mChild.moveY(Y);
	}

	void resizeWidth(float X)
	{
		mThemeButton.resizeWidth(X);
		mChild.resizeWidth(X);
	}

	void resizeHeight(float Y)
	{
		mThemeButton.resizeHeight(Y);
		mChild.resizeHeight(Y);
	}

	void setClipLeft(float X)
	{
		mThemeButton.setClipLeft(X);
		mChild.setClipLeft(X);
	}

	void setClipBottom(float Y)
	{
		mThemeButton.setClipBottom(Y);
		mChild.setClipBottom(Y);
	}

	void setClipRight(float X)
	{
		mThemeButton.setClipRight(X);
		mChild.setClipRight(X);
	}

	void setClipTop(float Y)
	{
		mThemeButton.setClipTop(Y);
		mChild.setClipTop(Y);
	}

	float getLeft() const
	{
		return mThemeButton.getLeft();
	}

	float getBottom() const
	{
		return mThemeButton.getBottom();
	}

	float getRight() const
	{
		return mThemeButton.getRight();
	}

	float getTop() const
	{
		return mThemeButton.getTop();
	}

	float getClipLeft() const
	{
		return mThemeButton.getClipLeft();
	}

	float getClipBottom() const
	{
		return mThemeButton.getClipBottom();
	}

	float getClipRight() const
	{
		return mThemeButton.getClipRight();
	}

	float getClipTop() const
	{
		return mThemeButton.getClipTop();
	}

	float getBaseWidth() const
	{
		return mThemeButton.getBaseWidth(mChild.getBaseWidth());
	}

	float getBaseHeight() const
	{
		return mThemeButton.getBaseHeight(mChild.getBaseHeight());
	}

	void delegateMouse(float, float)
	{
		mWindow->getMouseManager().setHandler(*this);
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

	void releaseMouse(float X, float Y) final
	{
		mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleButtonPress(float, float, std::uint8_t Index) final
	{
		if (Index == 1)
		{
			mIsPressed = true;
			mThemeButton.setIsDown(true);
		}
	}

	void handleButtonRelease(float X, float Y, std::uint8_t Index) final
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

	void handleMouseMotion(float X, float Y) final
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
