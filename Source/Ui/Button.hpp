#pragma once

#include "Container.hpp"
#include "Event.hpp"
#include "Window.hpp"
#include "Gl/Context.hpp"
#include "Theme/Button.hpp"

#include <stdexcept>

namespace Twil {
namespace Ui {

class WindowBaseT;

/// \brief A Widget that can be clicked to activate an event.
/// \param T Type of the child widget.
template<typename T>
class ButtonT :
	public ContainerT,
	public MouseHandlerT
{
	private:
	ContainerT & mParent;
	WindowBaseT & mWindow;
	Theme::ButtonT mThemeButton;
	T mChild;
	bool mIsPressed;
	bool mHasMouse;

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
	//Button
	EventT<> Clicked;

	ButtonT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mWindow(Window), // Gcc bug prevents brace initialization syntax here
		mThemeButton{Theme},
		mChild{*this, Window, Theme},
		mIsPressed{false},
		mHasMouse{false}
	{
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
	void moveX(signed short X)
	{
		mThemeButton.moveX(X);
		mChild.moveX(X);
	}

	void moveY(signed short Y)
	{
		mThemeButton.moveY(Y);
		mChild.moveY(Y);
	}

	void resizeWidth(signed short X)
	{
		mThemeButton.resizeWidth(X);
		mChild.resizeWidth(X);
	}

	void resizeHeight(signed short Y)
	{
		mThemeButton.resizeHeight(Y);
		mChild.resizeHeight(Y);
	}

	void setClipLeft(signed short X)
	{
		mThemeButton.setClipLeft(X);
		mChild.setClipLeft(X);
	}

	void setClipBottom(signed short Y)
	{
		mThemeButton.setClipBottom(Y);
		mChild.setClipBottom(Y);
	}

	void setClipRight(signed short X)
	{
		mThemeButton.setClipRight(X);
		mChild.setClipRight(X);
	}

	void setClipTop(signed short Y)
	{
		mThemeButton.setClipTop(Y);
		mChild.setClipTop(Y);
	}

	signed short getLeft() const
	{
		return mThemeButton.getLeft();
	}

	signed short getBottom() const
	{
		return mThemeButton.getBottom();
	}

	signed short getRight() const
	{
		return mThemeButton.getRight();
	}

	signed short getTop() const
	{
		return mThemeButton.getTop();
	}

	signed short getClipLeft() const
	{
		return mThemeButton.getClipLeft();
	}

	signed short getClipBottom() const
	{
		return mThemeButton.getClipBottom();
	}

	signed short getClipRight() const
	{
		return mThemeButton.getClipRight();
	}

	signed short getClipTop() const
	{
		return mThemeButton.getClipTop();
	}

	signed short getBaseWidth() const
	{
		return mThemeButton.getBaseWidth(mChild.getBaseWidth());
	}

	signed short getBaseHeight() const
	{
		return mThemeButton.getBaseHeight(mChild.getBaseHeight());
	}

	void delegateMouse(signed short, signed short)
	{
		mWindow.setMouseHandler(*this);
		mHasMouse = true;
	}

	// Container
	void handleChildBaseWidthChanged(void *) final
	{
		mParent.handleChildBaseWidthChanged(this);
	}

	void handleChildBaseHeightChanged(void *) final
	{
		mParent.handleChildBaseHeightChanged(this);
	}

	void releaseMouse(signed short X, signed short Y) final
	{
		mParent.releaseMouse(X, Y);
	}

	// MouseHandler
	void handleButtonPress(signed short, signed short, unsigned char Index) final
	{
		if (Index == 1) {
			mIsPressed = true;
			mThemeButton.setIsDown(true);
			mWindow.markNeedsDraw();
		}
	}

	void handleButtonRelease(signed short X, signed short Y, unsigned char Index) final
	{
		if (Index == 1) {
			if (!mIsPressed) return;
			if (mHasMouse) {
				mIsPressed = false;
				mThemeButton.setIsDown(false);
				mWindow.markNeedsDraw();
				Clicked();
			}
			else {
				mIsPressed = false;
				mParent.releaseMouse(X, Y);
			}
		}
	}

	void handleMouseMotion(signed short X, signed short Y) final
	{
		auto HasMouse = checkThisContains(X, Y);

		if (mHasMouse && !HasMouse) {
			mHasMouse = false;
			if (mIsPressed) {
				mThemeButton.setIsDown(false);
				mWindow.markNeedsDraw();
			}
			else mParent.releaseMouse(X, Y);
		}
		else if (!mHasMouse && HasMouse) {
			mHasMouse = true;
			if (mIsPressed) {
				mThemeButton.setIsDown(true);
				mWindow.markNeedsDraw();
			}
		}
	}
};

}
}
