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

	bool checkThisContains(std::int16_t X, std::int16_t Y)
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
	void moveX(std::int16_t X)
	{
		mThemeButton.moveX(X);
		mChild.moveX(X);
	}

	void moveY(std::int16_t Y)
	{
		mThemeButton.moveY(Y);
		mChild.moveY(Y);
	}

	void resizeWidth(std::int16_t X)
	{
		mThemeButton.resizeWidth(X);
		mChild.resizeWidth(X);
	}

	void resizeHeight(std::int16_t Y)
	{
		mThemeButton.resizeHeight(Y);
		mChild.resizeHeight(Y);
	}

	void setClipLeft(std::int16_t X)
	{
		mThemeButton.setClipLeft(X);
		mChild.setClipLeft(X);
	}

	void setClipBottom(std::int16_t Y)
	{
		mThemeButton.setClipBottom(Y);
		mChild.setClipBottom(Y);
	}

	void setClipRight(std::int16_t X)
	{
		mThemeButton.setClipRight(X);
		mChild.setClipRight(X);
	}

	void setClipTop(std::int16_t Y)
	{
		mThemeButton.setClipTop(Y);
		mChild.setClipTop(Y);
	}

	std::int16_t getLeft() const
	{
		return mThemeButton.getLeft();
	}

	std::int16_t getBottom() const
	{
		return mThemeButton.getBottom();
	}

	std::int16_t getRight() const
	{
		return mThemeButton.getRight();
	}

	std::int16_t getTop() const
	{
		return mThemeButton.getTop();
	}

	std::int16_t getClipLeft() const
	{
		return mThemeButton.getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return mThemeButton.getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return mThemeButton.getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return mThemeButton.getClipTop();
	}

	std::int16_t getBaseWidth() const
	{
		return mThemeButton.getBaseWidth(mChild.getBaseWidth());
	}

	std::int16_t getBaseHeight() const
	{
		return mThemeButton.getBaseHeight(mChild.getBaseHeight());
	}

	void delegateMouse(std::int16_t, std::int16_t)
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

	void releaseMouse(std::int16_t X, std::int16_t Y) final
	{
		mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleButtonPress(std::int16_t, std::int16_t, unsigned char Index) final
	{
		if (Index == 1)
		{
			mIsPressed = true;
			mThemeButton.setIsDown(true);
		}
	}

	void handleButtonRelease(std::int16_t X, std::int16_t Y, unsigned char Index) final
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

	void handleMouseMotion(std::int16_t X, std::int16_t Y) final
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
