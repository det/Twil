#pragma once

#include "PartitionBoxFwd.hpp"

#include "Container.hpp"
#include "Data/Tuple.hpp"
#include "WindowBase.hpp"

#include <algorithm>

namespace Twil {
namespace Ui {

/// \brief Functionality shared by both horizontal and vertical partition boxes.
template<typename ChildrenT>
class PartitionBoxBaseT
:
	public ContainerT
{
	PartitionBoxBaseT(PartitionBoxBaseT const &) = delete;
	PartitionBoxBaseT & operator =(PartitionBoxBaseT const &) = delete;

protected:
	ContainerT * mParent;
	ChildrenT mChildren;

	static std::int16_t const mSize = std::tuple_size<ChildrenT>::value;

	bool checkThisContains(float X, float Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

public:
	// PartitionBoxBase
	PartitionBoxBaseT() = default;

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.init(*this, Window);
		});
	}

	/// \returns A reference to a child widget.
	///
	/// \param I Index of the child
	template<std::size_t I>
	typename std::tuple_element<I, ChildrenT>::type & getChild()
	{
		return std::get<I>(mChildren);
	}

	/// \returns A const reference to a child widget.
	///
	/// \param I Index of the child
	template<std::size_t I>
	typename std::tuple_element<I, ChildrenT>::type const & getChild() const
	{
		return std::get<I>(mChildren);
	}

	// Widget

	void moveX(float X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.moveX(X);
		});
	}

	void moveY(float Y)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.moveY(Y);
		});
	}

	void setClipLeft(float X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipLeft(X);
		});
	}

	void setClipBottom(float Y)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipBottom(Y);
		});
	}

	void setClipRight(float X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipRight(X);
		});
	}

	void setClipTop(float Y)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipTop(Y);
		});
	}

	float getLeft() const
	{
		return getChild<0>().getLeft();
	}

	float getBottom() const
	{
		return getChild<0>().getBottom();
	}

	float getRight() const
	{
		return getChild<mSize - 1>().getRight();
	}

	float getTop() const
	{
		return getChild<mSize - 1>().getTop();
	}

	float getClipLeft() const
	{
		return getChild<0>().getClipLeft();
	}

	float getClipBottom() const
	{
		return getChild<0>().getClipBottom();
	}

	float getClipRight() const
	{
		return getChild<mSize - 1>().getClipRight();
	}

	float getClipTop() const
	{
		return getChild<mSize - 1>().getClipTop();
	}

	float getMaxWidth()
	{
		float MaxWidth = 0;
		Data::iterate(mChildren, [&](auto & Child)
		{
			MaxWidth = std::max(MaxWidth, Child.getBaseWidth());
		});
		return MaxWidth;
	}

	float getMaxHeight()
	{
		float MaxHeight = 0;
		Data::iterate(mChildren, [&](auto & Child)
		{
			MaxHeight = std::max(MaxHeight, Child.getBaseHeight());
		});
		return MaxHeight;
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
};

/// \brief A horizontal partition box.
///
/// All children Share the parent's height. The width is split evenly among the children.
///
/// \param ChildrenT A std::tuple or std::array of child widgets.

template<typename ChildrenT>
class PartitionBoxT<true, ChildrenT>
:
	public PartitionBoxBaseT<ChildrenT>
{
private:
	using PartitionBoxBaseT<ChildrenT>::mParent;
	using PartitionBoxBaseT<ChildrenT>::mChildren;
	using PartitionBoxBaseT<ChildrenT>::mSize;
	using PartitionBoxBaseT<ChildrenT>::checkThisContains;
	using PartitionBoxBaseT<ChildrenT>::getMaxWidth;
	using PartitionBoxBaseT<ChildrenT>::getMaxHeight;

public:
	using PartitionBoxBaseT<ChildrenT>::getLeft;
	using PartitionBoxBaseT<ChildrenT>::getBottom;
	using PartitionBoxBaseT<ChildrenT>::getRight;
	using PartitionBoxBaseT<ChildrenT>::getTop;

	// Widget
	void resizeWidth(float X)
	{
		float Width = getRight() + X - getLeft();
		float BoxWidth = Width / mSize;
		auto Left = getLeft();

		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.moveX(Left - Child.getLeft());
			Child.resizeWidth(Left + BoxWidth - Child.getRight());
			Left += BoxWidth;
		});
	}

	void resizeHeight(float Y)
	{
		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.resizeHeight(Y);
		});
	}

	float getBaseWidth() const
	{
		return getMaxWidth() * mSize;
	}

	float getBaseHeight() const
	{
		return getMaxHeight();
	}

	void delegateMouse(float X, float Y)
	{
		Data::iterateUntil(mChildren, [=](auto & Child)
		{
			if (X < Child.getRight())
			{
				Child.delegateMouse(X, Y);
				return false;
			}
			return true;
		});
	}

	// Container
	void releaseMouse(float X, float Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent->releaseMouse(X, Y);
	}

};

/// \brief A vertical partition box.
///
/// All children Share the parent's width. The height is split evenly among the children.
///
/// \param ChildrenT A std::tuple or std::array of child widgets.

template<typename ChildrenT>
class PartitionBoxT<false, ChildrenT>
:
	public PartitionBoxBaseT<ChildrenT>
{
private:
	using PartitionBoxBaseT<ChildrenT>::mParent;
	using PartitionBoxBaseT<ChildrenT>::mChildren;
	using PartitionBoxBaseT<ChildrenT>::mSize;
	using PartitionBoxBaseT<ChildrenT>::checkThisContains;
	using PartitionBoxBaseT<ChildrenT>::getMaxWidth;
	using PartitionBoxBaseT<ChildrenT>::getMaxHeight;

public:
	using PartitionBoxBaseT<ChildrenT>::getLeft;
	using PartitionBoxBaseT<ChildrenT>::getBottom;
	using PartitionBoxBaseT<ChildrenT>::getRight;
	using PartitionBoxBaseT<ChildrenT>::getTop;

	// Widget
	void resizeWidth(float X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.resizeWidth(X);
		});
	}

	void resizeHeight(float Y)
	{
		float Height = getTop() + Y - getBottom();
		float BoxHeight = Height / mSize;
		auto Bottom = getBottom();

		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.moveY(Bottom - Child.getBottom());
			Child.resizeHeight(Bottom + BoxHeight - Child.getTop());
			Bottom += BoxHeight;
		});
	}

	float getBaseWidth() const
	{
		return getMaxWidth();
	}

	float getBaseHeight() const
	{
		return getMaxHeight() * mSize;
	}

	void delegateMouse(float X, float Y)
	{
		Data::iterateUntil(mChildren, [=](auto & Child)
		{
			if (Y < Child.getTop())
			{
				Child.delegateMouse(X, Y);
				return false;
			}
			return true;
		});
	}

	// Container
	void releaseMouse(float X, float Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent->releaseMouse(X, Y);
	}
};

}
}
