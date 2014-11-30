#pragma once

#include "split_box.hxx"

#include "container.hpp"
#include "window_base.hpp"

namespace twil {
namespace ui {

/// \brief Functionality shared by all split boxes.
template<typename First, typename Second>
class SplitBoxBase
:
	public Container
{
	SplitBoxBase(SplitBoxBase const &) = delete;
	SplitBoxBase & operator =(SplitBoxBase const &) = delete;

protected:
	Container * parent_;
	First first_;
	Second second_;

	Dip GetMouseLeft() const
	{
		return std::max(GetLeft(), GetClipLeft());
	}

	Dip GetMouseRight() const
	{
		return std::min(GetRight(), GetClipRight());
	}

	Dip GetMouseBottom() const
	{
		return std::max(GetBottom(), GetClipBottom());
	}

	Dip GetMouseTop() const
	{
		return std::min(GetTop(), GetClipTop());
	}

	bool CheckThisContains(Dip x, Dip y) const
	{
		return (
			x >= GetMouseLeft() && x >= GetClipLeft() &&
			x <= GetMouseRight() && x <= GetClipRight() &&
			y >= GetMouseBottom() && y >= GetClipBottom() &&
			y <= GetMouseTop() && y <= GetClipTop());
	}

public:
	// SplitBox
	SplitBoxBase() = default;

	void Init(Container & parent, WindowBase & window)
	{
		parent_ = &parent;
		first_.Init(*this, window);
		second_.Init(*this, window);
	}

	/// \returns a reference to the first child.
	First & GetFirst()
	{
		return first_;
	}

	/// \returns a const reference to the first child.
	First const & GetFirst() const
	{
		return first_;
	}

	/// \returns a reference to the second child.
	Second & GetSecond()
	{
		return second_;
	}

	/// \returns a const reference to the second child.
	Second const & GetSecond() const
	{
		return second_;
	}

	// Widget
	void MoveX(Dip x)
	{
		first_.MoveX(x);
		second_.MoveX(x);
	}

	void MoveY(Dip y)
	{
		first_.MoveY(y);
		second_.MoveY(y);
	}

	Dip GetLeft() const
	{
		return first_.GetLeft();
	}

	Dip GetBottom() const
	{
		return first_.GetBottom();
	}

	Dip GetRight() const
	{
		return second_.GetRight();
	}

	Dip GetTop() const
	{
		return second_.GetTop();
	}

	Dip GetClipLeft() const
	{
		return first_.GetClipLeft();
	}

	Dip GetClipBottom() const
	{
		return first_.GetClipBottom();
	}

	Dip GetClipRight() const
	{
		return second_.GetClipRight();
	}

	Dip GetClipTop() const
	{
		return second_.GetClipTop();
	}
};

/// \brief Functionality shared by all horizontal split boxes.
template<typename First, typename Second>
class SplitBoxHorizontal
:
	public SplitBoxBase<First, Second>
{
protected:
	using SplitBoxBase<First, Second>::parent_;
	using SplitBoxBase<First, Second>::first_;
	using SplitBoxBase<First, Second>::second_;
	using SplitBoxBase<First, Second>::CheckThisContains;

public:
	// Widget
	void ResizeHeight(Dip y)
	{
		first_.ResizeHeight(y);
		second_.ResizeHeight(y);
	}

	void SetClipBottom(Dip y)
	{
		first_.SetClipBottom(y);
		second_.SetClipBottom(y);
	}

	void SetClipTop(Dip y)
	{
		first_.SetClipTop(y);
		second_.SetClipTop(y);
	}

	Dip GetBaseWidth() const
	{
		return first_.GetBaseWidth() + second_.GetBaseWidth();
	}

	Dip GetBaseHeight() const
	{
		return std::max(first_.GetBaseHeight(), second_.GetBaseHeight());
	}

	void DelegateMouse(Dip x, Dip y)
	{
		if (x < second_.GetLeft()) first_.DelegateMouse(x, y);
		else second_.DelegateMouse(x, y);
	}

	// Container
	void ReleaseMouse(Dip x, Dip y) final
	{
		if (CheckThisContains(x, y)) DelegateMouse(x, y);
		else parent_->ReleaseMouse(x, y);
	}

	void HandleChildBaseHeightChanged(void *) final
	{
		parent_->HandleChildBaseHeightChanged(this);
	}
};

/// \brief Functionality shared by all vertical split boxes.
template<typename First, typename Second>
class SplitBoxVertical
:
	public SplitBoxBase<First, Second>
{
protected:
	using SplitBoxBase<First, Second>::parent_;
	using SplitBoxBase<First, Second>::first_;
	using SplitBoxBase<First, Second>::second_;
	using SplitBoxBase<First, Second>::CheckThisContains;

public:
	// Widget
	void ResizeWidth(Dip x)
	{
		first_.ResizeWidth(x);
		second_.ResizeWidth(x);
	}

	void SetClipLeft(Dip x)
	{
		first_.SetClipLeft(x);
		second_.SetClipLeft(x);
	}

	void SetClipRight(Dip x)
	{
		first_.SetClipRight(x);
		second_.SetClipRight(x);
	}

	Dip GetBaseWidth() const
	{
		return std::max(first_.GetBaseWidth(), second_.GetBaseWidth());
	}

	Dip GetBaseHeight() const
	{
		return first_.GetBaseHeight() + second_.GetBaseHeight();
	}

	void DelegateMouse(Dip x, Dip y)
	{
		if (y < second_.GetBottom()) first_.DelegateMouse(x, y);
		else second_.DelegateMouse(x, y);
	}

	// Container
	void ReleaseMouse(Dip x, Dip y) final
	{
		if (CheckThisContains(x, y)) DelegateMouse(x, y);
		else parent_->ReleaseMouse(x, y);
	}

	void HandleChildBaseWidthChanged(void *) final
	{
		parent_->HandleChildBaseWidthChanged(this);
	}
};

/// \brief A horizontal split box where the first child is fixed width.
///
/// Both children share the parent's height.
/// The first child is kept at its base width and clipped if neccesary.
/// The second child has its width set to any remaining space.

template<typename First, typename Second>
class SplitBox<true, true, First, Second>
:
	public SplitBoxHorizontal<First, Second>
{
protected:
	using SplitBoxHorizontal<First, Second>::parent_;
	using SplitBoxHorizontal<First, Second>::first_;
	using SplitBoxHorizontal<First, Second>::second_;
	using SplitBoxHorizontal<First, Second>::GetMouseRight;

	void layout()
	{
		Dip delta = first_.GetLeft() + first_.GetBaseWidth() - first_.GetRight();
		first_.ResizeWidth(delta);
		second_.MoveX(delta);
		second_.ResizeWidth(-delta);
		first_.SetClipRight(GetMouseRight());
	}

public:
	// SplitBox
	void Init(Container & parent, WindowBase & window)
	{
		SplitBoxHorizontal<First, Second>::Init(parent, window);
		layout();
	}

	// Widget
	void ResizeWidth(Dip x)
	{
		second_.ResizeWidth(x);
		first_.SetClipRight(GetMouseRight());
	}

	void SetClipLeft(Dip x)
	{
		first_.SetClipLeft(x);
		second_.SetClipLeft(x);
	}

	void SetClipRight(Dip x)
	{
		first_.SetClipRight(GetMouseRight());
		second_.SetClipRight(x);
	}

	// Container
	void HandleChildBaseWidthChanged(void * child) final
	{
		if (child == &first_) layout();
		parent_->HandleChildBaseWidthChanged(this);
	}
};

/// \brief A horizontal split box where the second child is fixed width.
///
/// Both children share the parent's height.
/// The second child is kept at its base width and clipped if neccesary.
/// The first child has its width set to any remaining space.

template<typename First, typename Second>
class SplitBox<true, false, First, Second>
:
	public SplitBoxHorizontal<First, Second>
{
protected:
	using SplitBoxHorizontal<First, Second>::parent_;
	using SplitBoxHorizontal<First, Second>::first_;
	using SplitBoxHorizontal<First, Second>::second_;
	using SplitBoxHorizontal<First, Second>::GetMouseLeft;

	void layout()
	{
		Dip delta = second_.GetLeft() + second_.GetBaseWidth() - second_.GetRight();
		first_.ResizeWidth(-delta);
		second_.MoveX(-delta);
		second_.ResizeWidth(delta);
		second_.SetClipLeft(GetMouseLeft());
	}

public:
	// SplitBox
	void Init(Container & parent, WindowBase & window)
	{
		SplitBoxHorizontal<First, Second>::Init(parent, window);
		layout();
	}

	// Widget
	void ResizeWidth(Dip x)
	{
		first_.ResizeWidth(x);
		second_.MoveX(x);
		second_.SetClipLeft(GetMouseLeft());
	}

	void SetClipLeft(Dip x)
	{
		first_.SetClipLeft(x);
		second_.SetClipLeft(GetMouseLeft());
	}

	void SetClipRight(Dip x)
	{
		first_.SetClipRight(x);
		second_.SetClipRight(x);
	}

	// Container
	void HandleChildBaseWidthChanged(void * child) final
	{
		if (child == &second_) layout();
		parent_->HandleChildBaseWidthChanged(this);
	}
};

/// \brief A vertical split box where the first child is fixed height.
///
/// Both children share the parent's width.
/// The first child is kept at its base height and clipped if neccesary.
/// The second child has its height set to any remaining space.

template<typename First, typename Second>
class SplitBox<false, true, First, Second>
:
	public SplitBoxVertical<First, Second>
{
protected:
	using SplitBoxVertical<First, Second>::parent_;
	using SplitBoxVertical<First, Second>::first_;
	using SplitBoxVertical<First, Second>::second_;
	using SplitBoxVertical<First, Second>::GetMouseTop;

	void layout()
	{
		Dip delta = first_.GetBottom() + first_.GetBaseHeight() - first_.GetTop();
		first_.ResizeHeight(delta);
		second_.MoveY(delta);
		second_.ResizeHeight(-delta);
		first_.SetClipTop(GetMouseTop());
	}

public:
	// SplitBox
	void Init(Container & parent, WindowBase & window)
	{
		SplitBoxVertical<First, Second>::Init(parent, window);
		layout();
	}

	// Widget
	void ResizeHeight(Dip y)
	{
		second_.ResizeHeight(y);
		first_.SetClipTop(GetMouseTop());
	}

	void SetClipBottom(Dip y)
	{
		first_.SetClipBottom(y);
		second_.SetClipBottom(y);
	}

	void SetClipTop(Dip y)
	{
		first_.SetClipTop(GetMouseTop());
		second_.SetClipTop(y);
	}

	// Container
	void HandleChildBaseHeightChanged(void * child) final
	{
		if (child == &first_) layout();
		parent_->HandleChildBaseHeightChanged(this);
	}
};

/// \brief A vertical split box where the second child is fixed height.
///
/// Both children share the parent's width.
/// The second child is kept at its base height and clipped if neccesary.
/// The first child has its height set to any remaining space.

template<typename First, typename Second>
class SplitBox<false, false, First, Second>
:
	public SplitBoxVertical<First, Second>
{
protected:
	using SplitBoxVertical<First, Second>::parent_;
	using SplitBoxVertical<First, Second>::first_;
	using SplitBoxVertical<First, Second>::second_;
	using SplitBoxVertical<First, Second>::GetMouseBottom;

	void layout()
	{
		Dip delta = second_.GetBottom() + second_.GetBaseHeight() - second_.GetTop();
		first_.ResizeHeight(-delta);
		second_.MoveY(-delta);
		second_.ResizeHeight(delta);
		second_.SetClipBottom(GetMouseBottom());
	}

public:
	// SplitBox
	void Init(Container & parent, WindowBase & window)
	{
		SplitBoxVertical<First, Second>::Init(parent, window);
		layout();
	}

	// Widget
	void ResizeHeight(Dip y)
	{
		first_.ResizeHeight(y);
		second_.MoveY(y);
		second_.SetClipBottom(GetMouseBottom());
	}

	void SetClipBottom(Dip y)
	{
		first_.SetClipBottom(y);
		second_.SetClipBottom(GetMouseBottom());
	}

	void SetClipTop(Dip y)
	{
		first_.SetClipTop(y);
		second_.SetClipTop(y);
	}

	// Container
	void HandleChildBaseHeightChanged(void * child) final
	{
		if (child == &second_) layout();
		parent_->HandleChildBaseHeightChanged(this);
	}
};

}
}
