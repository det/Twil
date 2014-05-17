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

	bool checkThisContains(DipT X, DipT Y)
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

	void moveX(DipT X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.moveX(X);
		});
	}

	void moveY(DipT Y)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.moveY(Y);
		});
	}

	void setClipLeft(DipT X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipLeft(X);
		});
	}

	void setClipBottom(DipT Y)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipBottom(Y);
		});
	}

	void setClipRight(DipT X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipRight(X);
		});
	}

	void setClipTop(DipT Y)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.setClipTop(Y);
		});
	}

	DipT getLeft() const
	{
		return getChild<0>().getLeft();
	}

	DipT getBottom() const
	{
		return getChild<0>().getBottom();
	}

	DipT getRight() const
	{
		return getChild<mSize - 1>().getRight();
	}

	DipT getTop() const
	{
		return getChild<mSize - 1>().getTop();
	}

	DipT getClipLeft() const
	{
		return getChild<0>().getClipLeft();
	}

	DipT getClipBottom() const
	{
		return getChild<0>().getClipBottom();
	}

	DipT getClipRight() const
	{
		return getChild<mSize - 1>().getClipRight();
	}

	DipT getClipTop() const
	{
		return getChild<mSize - 1>().getClipTop();
	}

	DipT getMaxWidth() const
	{
		DipT MaxWidth = 0;
		Data::iterate(mChildren, [&](auto & Child)
		{
			MaxWidth = std::max(MaxWidth, Child.getBaseWidth());
		});
		return MaxWidth;
	}

	DipT getMaxHeight() const
	{
		DipT MaxHeight = 0;
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
	void resizeWidth(DipT X)
	{
		DipT Width = getRight() + X - getLeft();
		DipT BoxWidth = Width / mSize;
		auto Left = getLeft();

		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.moveX(Left - Child.getLeft());
			Child.resizeWidth(Left + BoxWidth - Child.getRight());
			Left += BoxWidth;
		});
	}

	void resizeHeight(DipT Y)
	{
		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.resizeHeight(Y);
		});
	}

	DipT getBaseWidth() const
	{
		return getMaxWidth() * mSize;
	}

	DipT getBaseHeight() const
	{
		return getMaxHeight();
	}

	void delegateMouse(DipT X, DipT Y)
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
	void releaseMouse(DipT X, DipT Y) final
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
	void resizeWidth(DipT X)
	{
		Data::iterate(mChildren, [=](auto & Child)
		{
			Child.resizeWidth(X);
		});
	}

	void resizeHeight(DipT Y)
	{
		DipT Height = getTop() + Y - getBottom();
		DipT BoxHeight = Height / mSize;
		auto Bottom = getBottom();

		Data::iterate(mChildren, [&](auto & Child)
		{
			Child.moveY(Bottom - Child.getBottom());
			Child.resizeHeight(Bottom + BoxHeight - Child.getTop());
			Bottom += BoxHeight;
		});
	}

	DipT getBaseWidth() const
	{
		return getMaxWidth();
	}

	DipT getBaseHeight() const
	{
		return getMaxHeight() * mSize;
	}

	void delegateMouse(DipT X, DipT Y)
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
	void releaseMouse(DipT X, DipT Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent->releaseMouse(X, Y);
	}
};

}
}
