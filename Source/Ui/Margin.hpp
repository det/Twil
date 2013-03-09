#pragma once

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
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
	public MouseHandlerT
{
	ContainerT * mParent;
	WindowBaseT * mWindow;
	T mChild;

	bool checkThisContains(signed short X, signed short Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop()
		);
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
	void init(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Manager)
	{
		mParent = &Parent;
		mWindow = &Window;

		mChild.init(*this, Window, Manager);
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
	void moveX(signed short X)
	{
		mChild.moveX(X);
	}

	void moveY(signed short Y)
	{
		mChild.moveY(Y);
	}

	void resizeWidth(signed short X)
	{
		mChild.resizeWidth(X);
	}

	void resizeHeight(signed short Y)
	{
		mChild.resizeHeight(Y);
	}

	void setClipLeft(signed short X)
	{
		mChild.setClipLeft(X);
	}

	void setClipRight(signed short X)
	{
		mChild.setClipRight(X);
	}

	void setClipBottom(signed short Y)
	{
		mChild.setClipBottom(Y);
	}

	void setClipTop(signed short Y)
	{
		mChild.setClipTop(Y);
	}

	signed short getLeft() const
	{
		return mChild.getLeft() - SpaceX;
	}

	signed short getBottom() const
	{
		return mChild.getBottom() - SpaceY;
	}

	signed short getRight() const
	{
		return mChild.getRight() + SpaceY;
	}

	signed short getTop() const
	{
		return mChild.getTop() + SpaceY;
	}

	signed short getClipLeft() const
	{
		return mChild.getClipLeft();
	}

	signed short getClipBottom() const
	{
		return mChild.getClipBottom();
	}

	signed short getClipRight() const
	{
		return mChild.getClipRight();
	}

	signed short getClipTop() const
	{
		return mChild.getClipTop();
	}

	signed short getBaseWidth() const
	{
		return mChild.getBaseWidth() + SpaceX + SpaceX;
	}

	signed short getBaseHeight() const
	{
		return mChild.getBaseHeight() + SpaceY + SpaceY;
	}

	void delegateMouse(signed short X, signed short Y)
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		else mWindow->setMouseHandler(*this);
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
		if (checkThisContains(X, Y)) mWindow->setMouseHandler(*this);
		else mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
