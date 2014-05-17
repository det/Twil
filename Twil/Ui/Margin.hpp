#pragma once

#include "MarginFwd.hpp"

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"

namespace Twil {
namespace Ui {

/// \brief Provides a fixed size margin around a child
///
/// \param SpaceX Size of the left and right margins.
/// \param SpaceY Size of the bottom and top margins.
/// \param T Type of the child widget.
template<DipT SpaceX, DipT SpaceY, typename T>
class MarginT
:
	public ContainerT,
	public MouseHandlerT
{
	MarginT(MarginT const &) = delete;
	MarginT & operator =(MarginT const &) = delete;

private:
	ContainerT * mParent;
	WindowBaseT * mWindow;
	T mChild;

	bool checkThisContains(DipT X, DipT Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

	bool checkChildContains(DipT X, DipT Y)
	{
		return (
			X >= mChild.getLeft() && X <= mChild.getRight() &&
			Y >= mChild.getBottom() && Y <= mChild.getTop());
	}

public:
	// Margin
	MarginT() = default;

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		mWindow = &Window;

		mChild.init(*this, Window);
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
	void moveX(DipT X)
	{
		mChild.moveX(X);
	}

	void moveY(DipT Y)
	{
		mChild.moveY(Y);
	}

	void resizeWidth(DipT X)
	{
		mChild.resizeWidth(X);
	}

	void resizeHeight(DipT Y)
	{
		mChild.resizeHeight(Y);
	}

	void setClipLeft(DipT X)
	{
		mChild.setClipLeft(X);
	}

	void setClipRight(DipT X)
	{
		mChild.setClipRight(X);
	}

	void setClipBottom(DipT Y)
	{
		mChild.setClipBottom(Y);
	}

	void setClipTop(DipT Y)
	{
		mChild.setClipTop(Y);
	}

	DipT getLeft() const
	{
		return mChild.getLeft() - SpaceX;
	}

	DipT getBottom() const
	{
		return mChild.getBottom() - SpaceY;
	}

	DipT getRight() const
	{
		return mChild.getRight() + SpaceY;
	}

	DipT getTop() const
	{
		return mChild.getTop() + SpaceY;
	}

	DipT getClipLeft() const
	{
		return mChild.getClipLeft();
	}

	DipT getClipBottom() const
	{
		return mChild.getClipBottom();
	}

	DipT getClipRight() const
	{
		return mChild.getClipRight();
	}

	DipT getClipTop() const
	{
		return mChild.getClipTop();
	}

	DipT getBaseWidth() const
	{
		return mChild.getBaseWidth() + SpaceX + SpaceX;
	}

	DipT getBaseHeight() const
	{
		return mChild.getBaseHeight() + SpaceY + SpaceY;
	}

	void delegateMouse(DipT X, DipT Y)
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

	void releaseMouse(DipT X, DipT Y) final
	{
		if (checkThisContains(X, Y)) mWindow->setMouseHandler(*this);
		else mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleMouseMotion(DipT X, DipT Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
