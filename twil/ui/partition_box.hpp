#pragma once

#include "partition_box.hxx"

#include "container.hpp"
#include "data/tuple.hpp"
#include "window_base.hpp"

#include <algorithm>

namespace twil {
namespace ui {

/// \brief Functionality shared by both horizontal and vertical partition boxes.
template<typename Children>
class PartitionBoxBase
:
	public Container
{
	PartitionBoxBase(PartitionBoxBase const &) = delete;
	PartitionBoxBase & operator =(PartitionBoxBase const &) = delete;

protected:
	Container * parent_;
	Children children_;

	static Pixel const size_ = std::tuple_size<Children>::value;

	bool CheckThisContains(Dip x, Dip y)
	{
		return (
			x >= GetLeft() && x >= GetClipLeft() &&
			x <= GetRight() && x <= GetClipRight() &&
			y >= GetBottom() && y >= GetClipBottom() &&
			y <= GetTop() && y <= GetClipTop());
	}

public:
	// PartitionBoxBase
	PartitionBoxBase() = default;

	void Init(Container & parent, WindowBase & window)
	{
		parent_ = &parent;
		data::Iterate(children_, [&](auto & child)
		{
			child.Init(*this, window);
		});
	}

	/// \returns A reference to a child widget.
	///
	/// \param i Index of the child
	template<std::size_t i>
	typename std::tuple_element<i, Children>::type & GetChild()
	{
		return std::get<i>(children_);
	}

	/// \returns A const reference to a child widget.
	///
	/// \param i Index of the child
	template<std::size_t i>
	typename std::tuple_element<i, Children>::type const & GetChild() const
	{
		return std::get<i>(children_);
	}

	// Widget

	void MoveX(Dip x)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.MoveX(x);
		});
	}

	void MoveY(Dip y)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.MoveY(y);
		});
	}

	void SetClipLeft(Dip x)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.SetClipLeft(x);
		});
	}

	void SetClipBottom(Dip y)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.SetClipBottom(y);
		});
	}

	void SetClipRight(Dip x)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.SetClipRight(x);
		});
	}

	void SetClipTop(Dip y)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.SetClipTop(y);
		});
	}

	Dip GetLeft() const
	{
		return GetChild<0>().GetLeft();
	}

	Dip GetBottom() const
	{
		return GetChild<0>().GetBottom();
	}

	Dip GetRight() const
	{
		return GetChild<size_ - 1>().GetRight();
	}

	Dip GetTop() const
	{
		return GetChild<size_ - 1>().GetTop();
	}

	Dip GetClipLeft() const
	{
		return GetChild<0>().GetClipLeft();
	}

	Dip GetClipBottom() const
	{
		return GetChild<0>().GetClipBottom();
	}

	Dip GetClipRight() const
	{
		return GetChild<size_ - 1>().GetClipRight();
	}

	Dip GetClipTop() const
	{
		return GetChild<size_ - 1>().GetClipTop();
	}

	Dip GetMaxWidth() const
	{
		Dip max_width = 0;
		data::Iterate(children_, [&](auto & child)
		{
			max_width = std::max(max_width, child.GetBaseWidth());
		});
		return max_width;
	}

	Dip GetMaxHeight() const
	{
		Dip max_height = 0;
		data::Iterate(children_, [&](auto & child)
		{
			max_height = std::max(max_height, child.GetBaseHeight());
		});
		return max_height;
	}

	// Container
	void HandleChildBaseWidthChanged(void *) final
	{
		parent_->HandleChildBaseWidthChanged(this);
	}

	void HandleChildBaseHeightChanged(void *) final
	{
		parent_->HandleChildBaseHeightChanged(this);
	}
};

/// \brief A horizontal partition box.
///
/// All children Share the parent's height. The width is split evenly among the children.
///
/// \param Children A std::tuple or std::array of child widgets.

template<typename Children>
class PartitionBox<true, Children>
:
	public PartitionBoxBase<Children>
{
private:
	using PartitionBoxBase<Children>::parent_;
	using PartitionBoxBase<Children>::children_;
	using PartitionBoxBase<Children>::size_;
	using PartitionBoxBase<Children>::CheckThisContains;
	using PartitionBoxBase<Children>::GetMaxWidth;
	using PartitionBoxBase<Children>::GetMaxHeight;

public:
	using PartitionBoxBase<Children>::GetLeft;
	using PartitionBoxBase<Children>::GetBottom;
	using PartitionBoxBase<Children>::GetRight;
	using PartitionBoxBase<Children>::GetTop;

	// Widget
	void ResizeWidth(Dip x)
	{
		Dip width = GetRight() + x - GetLeft();
		Dip box_width = width / size_;
		auto left = GetLeft();

		data::Iterate(children_, [&](auto & child)
		{
			child.MoveX(left - child.GetLeft());
			child.ResizeWidth(left + box_width - child.GetRight());
			left += box_width;
		});
	}

	void ResizeHeight(Dip y)
	{
		data::Iterate(children_, [&](auto & child)
		{
			child.ResizeHeight(y);
		});
	}

	Dip GetBaseWidth() const
	{
		return GetMaxWidth() * size_;
	}

	Dip GetBaseHeight() const
	{
		return GetMaxHeight();
	}

	void DelegateMouse(Dip x, Dip y)
	{
		data::IterateUntil(children_, [=](auto & child)
		{
			if (x < child.GetRight())
			{
				child.DelegateMouse(x, y);
				return false;
			}
			return true;
		});
	}

	// Container
	void ReleaseMouse(Dip x, Dip y) final
	{
		if (CheckThisContains(x, y)) DelegateMouse(x, y);
		else parent_->ReleaseMouse(x, y);
	}

};

/// \brief A vertical partition box.
///
/// All children Share the parent's width. The height is split evenly among the children.
///
/// \param Children A std::tuple or std::array of child widgets.

template<typename Children>
class PartitionBox<false, Children>
:
	public PartitionBoxBase<Children>
{
private:
	using PartitionBoxBase<Children>::parent_;
	using PartitionBoxBase<Children>::children_;
	using PartitionBoxBase<Children>::size_;
	using PartitionBoxBase<Children>::CheckThisContains;
	using PartitionBoxBase<Children>::GetMaxWidth;
	using PartitionBoxBase<Children>::GetMaxHeight;

public:
	using PartitionBoxBase<Children>::GetLeft;
	using PartitionBoxBase<Children>::GetBottom;
	using PartitionBoxBase<Children>::GetRight;
	using PartitionBoxBase<Children>::GetTop;

	// Widget
	void ResizeWidth(Dip x)
	{
		data::Iterate(children_, [=](auto & child)
		{
			child.ResizeWidth(x);
		});
	}

	void ResizeHeight(Dip y)
	{
		Dip height = GetTop() + y - GetBottom();
		Dip box_height = height / size_;
		auto bottom = GetBottom();

		data::Iterate(children_, [&](auto & child)
		{
			child.MoveY(bottom - child.GetBottom());
			child.ResizeHeight(bottom + box_height - child.GetTop());
			bottom += box_height;
		});
	}

	Dip GetBaseWidth() const
	{
		return GetMaxWidth();
	}

	Dip GetBaseHeight() const
	{
		return GetMaxHeight() * size_;
	}

	void DelegateMouse(Dip x, Dip y)
	{
		data::IterateUntil(children_, [=](auto & child)
		{
			if (y < child.GetTop())
			{
				child.DelegateMouse(x, y);
				return false;
			}
			return true;
		});
	}

	// Container
	void ReleaseMouse(Dip x, Dip y) final
	{
		if (CheckThisContains(x, y)) DelegateMouse(x, y);
		else parent_->ReleaseMouse(x, y);
	}
};

}
}
