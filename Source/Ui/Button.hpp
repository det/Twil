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
	ContainerT * mParent;
	WindowBaseT * mWindow;
	Theme::ButtonT mTheme;
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

	void init(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Manager)
	{
		mParent = &Parent;
		mWindow = &Window;
		mIsPressed = false;
		mHasMouse = false;

		mTheme.init(Manager);
		mChild.init(*this, Window, Manager);
		auto LeftMargin = mTheme.getLeftMargin();
		auto RightMargin = mTheme.getRightMargin();
		auto BottomMargin = mTheme.getBottomMargin();
		auto TopMargin = mTheme.getTopMargin();
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
		mTheme.moveX(X);
		mChild.moveX(X);
	}

	void moveY(signed short Y)
	{
		mTheme.moveY(Y);
		mChild.moveY(Y);
	}

	void resizeWidth(signed short X)
	{
		mTheme.resizeWidth(X);
		mChild.resizeWidth(X);
	}

	void resizeHeight(signed short Y)
	{
		mTheme.resizeHeight(Y);
		mChild.resizeHeight(Y);
	}

	void setClipLeft(signed short X)
	{
		mTheme.setClipLeft(X);
		mChild.setClipLeft(X);
	}

	void setClipBottom(signed short Y)
	{
		mTheme.setClipBottom(Y);
		mChild.setClipBottom(Y);
	}

	void setClipRight(signed short X)
	{
		mTheme.setClipRight(X);
		mChild.setClipRight(X);
	}

	void setClipTop(signed short Y)
	{
		mTheme.setClipTop(Y);
		mChild.setClipTop(Y);
	}

	signed short getLeft() const
	{
		return mTheme.getLeft();
	}

	signed short getBottom() const
	{
		return mTheme.getBottom();
	}

	signed short getRight() const
	{
		return mTheme.getRight();
	}

	signed short getTop() const
	{
		return mTheme.getTop();
	}

	signed short getClipLeft() const
	{
		return mTheme.getClipLeft();
	}

	signed short getClipBottom() const
	{
		return mTheme.getClipBottom();
	}

	signed short getClipRight() const
	{
		return mTheme.getClipRight();
	}

	signed short getClipTop() const
	{
		return mTheme.getClipTop();
	}

	signed short getBaseWidth() const
	{
		return mTheme.getBaseWidth(mChild.getBaseWidth());
	}

	signed short getBaseHeight() const
	{
		return mTheme.getBaseHeight(mChild.getBaseHeight());
	}

	void delegateMouse(signed short, signed short)
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

	void releaseMouse(signed short X, signed short Y) final
	{
		mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleButtonPress(signed short, signed short, unsigned char Index) final
	{
		if (Index == 1) {
			mIsPressed = true;
			mTheme.setIsDown(true);
			mWindow->markNeedsDraw();
		}
	}

	void handleButtonRelease(signed short X, signed short Y, unsigned char Index) final
	{
		if (Index == 1) {
			if (!mIsPressed) return;
			if (mHasMouse) {
				mIsPressed = false;
				mTheme.setIsDown(false);
				mWindow->markNeedsDraw();
				Clicked();
			}
			else {
				mIsPressed = false;
				mParent->releaseMouse(X, Y);
			}
		}
	}

	void handleMouseMotion(signed short X, signed short Y) final
	{
		auto HasMouse = checkThisContains(X, Y);

		if (mHasMouse && !HasMouse) {
			mHasMouse = false;
			if (mIsPressed) {
				mTheme.setIsDown(false);
				mWindow->markNeedsDraw();
			}
			else mParent->releaseMouse(X, Y);
		}
		else if (!mHasMouse && HasMouse) {
			mHasMouse = true;
			if (mIsPressed) {
				mTheme.setIsDown(true);
				mWindow->markNeedsDraw();
			}
		}
	}
};

}
}
