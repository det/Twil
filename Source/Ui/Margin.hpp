#pragma once

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Widget.hpp"

#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

/// \brief Provides a fixed size margin around a child
///
/// \param SpaceX Size of the left and right margins.
/// \param SpaceY Size of the bottom and top margins.
/// \param T Type of the child widget.
template<unsigned short SpaceX, unsigned short SpaceY, typename T>
class MarginT :
	public ContainerT,
	public MouseHandlerT,
	public WidgetT
{
	ContainerT & mParent;
	WindowBaseT & mWindow;
	T mChild;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mRight = 0;
	signed short mTop = 0;

	bool checkThisContains(signed short X, signed short Y)
	{
		return X >= mLeft && X <= mRight &&	Y >= mBottom && Y <= mTop;
	}

	bool checkChildContains(signed short X, signed short Y)
	{
		return (
			X >= mChild.getLeft() && X <= mChild.getRight() &&
			Y >= mChild.getBottom() && Y <= mChild.getTop()
		);
	}

	public:
	// Margin
	MarginT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mWindow(Window), // Gcc bug prevents brace initialization syntax here
		mChild{*this, Window, Theme}
	{
		mChild.moveX(SpaceX);
		mChild.moveY(SpaceY);
		mChild.resizeWidth(-SpaceX * 2);
		mChild.resizeHeight(-SpaceY * 2);
	}

	/// \returns a reference to the child widget
	T & getChild()
	{
		return mChild;
	}

	/// \returns a const reference to the child widget
	T const & getChild() const
	{
		return mChild;
	}

	// Widget
	void moveX(signed short X) final
	{
		mLeft += X;
		mRight += X;
		mChild.moveX(X);
	}

	void moveY(signed short Y) final
	{
		mBottom += Y;
		mTop += Y;
		mChild.moveY(Y);
	}

	void resizeWidth(signed short X) final
	{
		mRight += X;
		mChild.resizeWidth(X);
	}

	void resizeHeight(signed short Y) final
	{
		mTop += Y;
		mChild.resizeHeight(Y);
	}

	void setClipLeft(signed short X) final
	{
		mChild.setClipLeft(X);
	}

	void setClipBottom(signed short Y) final
	{
		mChild.setClipBottom(Y);
	}

	void setClipRight(signed short X) final
	{
		mChild.setClipRight(X);
	}

	void setClipTop(signed short Y) final
	{
		mChild.setClipTop(Y);
	}

	void draw() const final
	{
		mChild.draw();
	}

	signed short getLeft() const final
	{
		return mLeft;
	}

	signed short getBottom() const final
	{
		return mBottom;
	}

	signed short getRight() const final
	{
		return mRight;
	}

	signed short getTop() const final
	{
		return mTop;
	}

	signed short getBaseWidth() const final
	{
		return mChild.getBaseWidth() + SpaceX + SpaceX;
	}

	signed short getBaseHeight() const final
	{
		return mChild.getBaseHeight() + SpaceY + SpaceY;
	}

	void delegateMouse(signed short X, signed short Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		else mWindow.setMouseHandler(*this);
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
		if (checkThisContains(X, Y)) mWindow.setMouseHandler(*this);
		else mParent.releaseMouse(X, Y);
	}

	// MouseHandler
	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		if (!checkThisContains(X, Y)) mParent.releaseMouse(X, Y);
	}
};

}
}
