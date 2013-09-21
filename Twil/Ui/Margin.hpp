#pragma once

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

	bool checkThisContains(std::int16_t X, std::int16_t Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

	bool checkChildContains(std::int16_t X, std::int16_t Y)
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
	void moveX(std::int16_t X)
	{
		mChild.moveX(X);
	}

	void moveY(std::int16_t Y)
	{
		mChild.moveY(Y);
	}

	void resizeWidth(std::int16_t X)
	{
		mChild.resizeWidth(X);
	}

	void resizeHeight(std::int16_t Y)
	{
		mChild.resizeHeight(Y);
	}

	void setClipLeft(std::int16_t X)
	{
		mChild.setClipLeft(X);
	}

	void setClipRight(std::int16_t X)
	{
		mChild.setClipRight(X);
	}

	void setClipBottom(std::int16_t Y)
	{
		mChild.setClipBottom(Y);
	}

	void setClipTop(std::int16_t Y)
	{
		mChild.setClipTop(Y);
	}

	std::int16_t getLeft() const
	{
		return mChild.getLeft() - SpaceX;
	}

	std::int16_t getBottom() const
	{
		return mChild.getBottom() - SpaceY;
	}

	std::int16_t getRight() const
	{
		return mChild.getRight() + SpaceY;
	}

	std::int16_t getTop() const
	{
		return mChild.getTop() + SpaceY;
	}

	std::int16_t getClipLeft() const
	{
		return mChild.getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return mChild.getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return mChild.getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return mChild.getClipTop();
	}

	std::int16_t getBaseWidth() const
	{
		return mChild.getBaseWidth() + SpaceX + SpaceX;
	}

	std::int16_t getBaseHeight() const
	{
		return mChild.getBaseHeight() + SpaceY + SpaceY;
	}

	void delegateMouse(std::int16_t X, std::int16_t Y)
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		else mWindow->getMouseManager().setHandler(*this);
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
		if (checkThisContains(X, Y)) mWindow->getMouseManager().setHandler(*this);
		else mParent->releaseMouse(X, Y);
	}

	// MouseHandler
	void handleMouseMotion(std::int16_t X, std::int16_t Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
