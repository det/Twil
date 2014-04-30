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
template<std::uint16_t SpaceX, std::uint16_t SpaceY, typename T>
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

	bool checkThisContains(float X, float Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

	bool checkChildContains(float X, float Y)
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
	void moveX(float X)
	{
		mChild.moveX(X);
	}

	void moveY(float Y)
	{
		mChild.moveY(Y);
	}

	void resizeWidth(float X)
	{
		mChild.resizeWidth(X);
	}

	void resizeHeight(float Y)
	{
		mChild.resizeHeight(Y);
	}

	void setClipLeft(float X)
	{
		mChild.setClipLeft(X);
	}

	void setClipRight(float X)
	{
		mChild.setClipRight(X);
	}

	void setClipBottom(float Y)
	{
		mChild.setClipBottom(Y);
	}

	void setClipTop(float Y)
	{
		mChild.setClipTop(Y);
	}

	float getLeft() const
	{
		return mChild.getLeft() - SpaceX;
	}

	float getBottom() const
	{
		return mChild.getBottom() - SpaceY;
	}

	float getRight() const
	{
		return mChild.getRight() + SpaceY;
	}

	float getTop() const
	{
		return mChild.getTop() + SpaceY;
	}

	float getClipLeft() const
	{
		return mChild.getClipLeft();
	}

	float getClipBottom() const
	{
		return mChild.getClipBottom();
	}

	float getClipRight() const
	{
		return mChild.getClipRight();
	}

	float getClipTop() const
	{
		return mChild.getClipTop();
	}

	float getBaseWidth() const
	{
		return mChild.getBaseWidth() + SpaceX + SpaceX;
	}

	float getBaseHeight() const
	{
		return mChild.getBaseHeight() + SpaceY + SpaceY;
	}

	void delegateMouse(float X, float Y)
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

	void releaseMouse(float X, float Y) final
	{
		if (checkThisContains(X, Y)) mWindow->setMouseHandler(*this);
		else mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleMouseMotion(float X, float Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
