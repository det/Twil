#pragma once

#include "Container.hpp"
#include "WindowBase.hpp"
#include "Data/Tuple.hpp"

#include <algorithm>

namespace Twil {

namespace Theme {
class ManagerT;
}

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

	struct InitFunctorT
	{
		ContainerT & Parent;
		WindowBaseT & Window;

		template<typename T>
		void operator()(T & Child)
		{
			Child.init(Parent, Window);
		}
	};

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		Data::iterate(mChildren, InitFunctorT{*this, Window});
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
	struct MoveXFunctorT
	{
		float X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveX(X);
		}
	};

	void moveX(float X)
	{
		Data::iterate(mChildren, MoveXFunctorT{X});
	}

	struct MoveYFunctorT
	{
		float Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveY(Y);
		}
	};

	void moveY(float Y)
	{
		Data::iterate(mChildren, MoveYFunctorT{Y});
	}

	struct SetClipLeftFunctorT
	{
		float X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipLeft(X);
		}
	};

	void setClipLeft(float X)
	{
		Data::iterate(mChildren, SetClipLeftFunctorT{X});
	}

	struct SetClipBottomFunctorT
	{
		float Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipBottom(Y);
		}
	};

	void setClipBottom(float Y)
	{
		Data::iterate(mChildren, SetClipBottomFunctorT{Y});
	}

	struct SetClipRightFunctorT
	{
		float X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipRight(X);
		}
	};

	void setClipRight(float X)
	{
		Data::iterate(mChildren, SetClipRightFunctorT{X});
	}

	struct SetClipTopFunctorT
	{
		float Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipTop(Y);
		}
	};

	void setClipTop(float Y)
	{
		Data::iterate(mChildren, SetClipTopFunctorT{Y});
	}

	struct DrawFunctorT
	{
		template<typename T>
		void operator()(T const & Child)
		{
			Child.draw();
		}
	};

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

	struct MaxWidthFunctorT
	{
		float & MaxWidth;

		template<typename T>
		void operator()(T const & Child)
		{
			MaxWidth = std::max(MaxWidth, Child.getBaseWidth());
		}
	};

	struct MaxHeightFunctorT
	{
		float & MaxHeight;

		template<typename T>
		void operator()(T const & Child)
		{
			MaxHeight = std::max(MaxHeight, Child.getBaseHeight());
		}
	};

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

template<bool IsHorizontal, typename ChildrenT>
class PartitionBoxT;

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
	using typename PartitionBoxBaseT<ChildrenT>::MaxWidthFunctorT;
	using typename PartitionBoxBaseT<ChildrenT>::MaxHeightFunctorT;

public:
	using PartitionBoxBaseT<ChildrenT>::getLeft;
	using PartitionBoxBaseT<ChildrenT>::getBottom;
	using PartitionBoxBaseT<ChildrenT>::getRight;
	using PartitionBoxBaseT<ChildrenT>::getTop;

	// Widget
	struct ResizeWidthFunctorT
	{
		float Left;
		float BoxWidth;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveX(Left - Child.getLeft());
			Child.resizeWidth(Left + BoxWidth - Child.getRight());
			Left += BoxWidth;
		}
	};

	void resizeWidth(float X)
	{
		float Width = getRight() + X - getLeft();
		float BoxWidth = Width / mSize;

		Data::iterate(mChildren, ResizeWidthFunctorT{getLeft(), BoxWidth});
	}

	struct ResizeHeightFunctorT
	{
		float Top;

		template<typename T>
		void operator()(T & Child)
		{
			Child.resizeHeight(Top);
		}
	};

	void resizeHeight(float Y)
	{
		Data::iterate(mChildren, ResizeHeightFunctorT{Y});
	}

	float getBaseWidth() const
	{
		float MaxWidth = 0;
		Data::iterate(mChildren, MaxWidthFunctorT{MaxWidth});
		return MaxWidth * mSize;
	}

	float getBaseHeight() const
	{
		float MaxHeight = 0;
		Data::iterate(mChildren, MaxHeightFunctorT{MaxHeight});
		return MaxHeight;
	}

	struct DelegateMouseFunctorT
	{
		float X;
		float Y;

		template<typename T>
		bool operator()(T & Child)
		{
			if (X < Child.getRight())
			{
				Child.delegateMouse(X, Y);
				return false;
			}
			return true;
		}
	};

	void delegateMouse(float X, float Y)
	{
		Data::iterateUntil(mChildren, DelegateMouseFunctorT{X, Y});
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
	using typename PartitionBoxBaseT<ChildrenT>::MaxWidthFunctorT;
	using typename PartitionBoxBaseT<ChildrenT>::MaxHeightFunctorT;

public:
	using PartitionBoxBaseT<ChildrenT>::getLeft;
	using PartitionBoxBaseT<ChildrenT>::getBottom;
	using PartitionBoxBaseT<ChildrenT>::getRight;
	using PartitionBoxBaseT<ChildrenT>::getTop;

	// Widget
	struct ResizeWidthFunctorT
	{
		float Right;

		template<typename T>
		void operator()(T & Child)
		{
			Child.resizeWidth(Right);
		}
	};

	void resizeWidth(float X)
	{
		Data::iterate(mChildren, ResizeWidthFunctorT{X});
	}

	struct ResizeHeightFunctorT
	{
		float Bottom;
		float BoxHeight;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveY(Bottom - Child.getBottom());
			Child.resizeHeight(Bottom + BoxHeight - Child.getTop());
			Bottom += BoxHeight;
		}
	};

	void resizeHeight(float Y)
	{
		float Height = getTop() + Y - getBottom();
		float BoxHeight = Height / mSize;

		Data::iterate(mChildren, ResizeHeightFunctorT{getBottom(), BoxHeight});
	}

	float getBaseWidth() const
	{
		float MaxWidth = 0;
		Data::iterate(mChildren, MaxWidthFunctorT{MaxWidth});
		return MaxWidth;
	}

	float getBaseHeight() const
	{
		float MaxHeight = 0;
		Data::iterate(mChildren, MaxHeightFunctorT{MaxHeight});
		return MaxHeight * mSize;
	}

	struct DelegateMouseFunctorT
	{
		float X;
		float Y;

		template<typename T>
		bool operator()(T & Child)
		{
			if (Y < Child.getTop())
			{
				Child.delegateMouse(X, Y);
				return false;
			}
			return true;
		}
	};

	void delegateMouse(float X, float Y)
	{
		Data::iterateUntil(mChildren, DelegateMouseFunctorT{X, Y});
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
