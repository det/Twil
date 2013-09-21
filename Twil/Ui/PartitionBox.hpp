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

	bool checkThisContains(std::int16_t X, std::int16_t Y)
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
		std::int16_t X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveX(X);
		}
	};

	void moveX(std::int16_t X)
	{
		Data::iterate(mChildren, MoveXFunctorT{X});
	}

	struct MoveYFunctorT
	{
		std::int16_t Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveY(Y);
		}
	};

	void moveY(std::int16_t Y)
	{
		Data::iterate(mChildren, MoveYFunctorT{Y});
	}

	struct SetClipLeftFunctorT
	{
		std::int16_t X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipLeft(X);
		}
	};

	void setClipLeft(std::int16_t X)
	{
		Data::iterate(mChildren, SetClipLeftFunctorT{X});
	}

	struct SetClipBottomFunctorT
	{
		std::int16_t Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipBottom(Y);
		}
	};

	void setClipBottom(std::int16_t Y)
	{
		Data::iterate(mChildren, SetClipBottomFunctorT{Y});
	}

	struct SetClipRightFunctorT
	{
		std::int16_t X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipRight(X);
		}
	};

	void setClipRight(std::int16_t X)
	{
		Data::iterate(mChildren, SetClipRightFunctorT{X});
	}

	struct SetClipTopFunctorT
	{
		std::int16_t Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipTop(Y);
		}
	};

	void setClipTop(std::int16_t Y)
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

	std::int16_t getLeft() const
	{
		return getChild<0>().getLeft();
	}

	std::int16_t getBottom() const
	{
		return getChild<0>().getBottom();
	}

	std::int16_t getRight() const
	{
		return getChild<mSize - 1>().getRight();
	}

	std::int16_t getTop() const
	{
		return getChild<mSize - 1>().getTop();
	}

	std::int16_t getClipLeft() const
	{
		return getChild<0>().getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return getChild<0>().getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return getChild<mSize - 1>().getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return getChild<mSize - 1>().getClipTop();
	}

	struct MaxWidthFunctorT
	{
		std::int16_t & MaxWidth;

		template<typename T>
		void operator()(T const & Child)
		{
			MaxWidth = std::max(MaxWidth, Child.getBaseWidth());
		}
	};

	struct MaxHeightFunctorT
	{
		std::int16_t & MaxHeight;

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
		std::int16_t Left;
		std::int16_t BoxWidth;
		std::int16_t Mod;
		std::int16_t Direction;

		template<typename T>
		void operator()(T & Child)
		{
			std::int16_t Width = BoxWidth;
			if (Mod > 0)
			{
				Width += Direction;
				--Mod;
			}
			Child.moveX(Left - Child.getLeft());
			Child.resizeWidth(Left + Width - Child.getRight());
			Left += Width;
		}
	};

	void resizeWidth(std::int16_t X)
	{
		std::int16_t Width = getRight() + X - getLeft();
		std::int16_t BoxWidth = Width / mSize;
		std::int16_t Mod;
		std::int16_t Direction;
		if (Width >= 0)
		{
			Mod = Width % mSize;
			Direction = 1;
		}
		else
		{
			Mod = -Width % mSize;
			Direction = -1;
		}
		Data::iterate(mChildren, ResizeWidthFunctorT{getLeft(), BoxWidth, Mod, Direction});
	}

	struct ResizeHeightFunctorT
	{
		std::int16_t Top;

		template<typename T>
		void operator()(T & Child)
		{
			Child.resizeHeight(Top);
		}
	};

	void resizeHeight(std::int16_t Y)
	{
		Data::iterate(mChildren, ResizeHeightFunctorT{Y});
	}

	std::int16_t getBaseWidth() const
	{
		std::int16_t MaxWidth = 0;
		Data::iterate(mChildren, MaxWidthFunctorT{MaxWidth});
		return MaxWidth * mSize;
	}

	std::int16_t getBaseHeight() const
	{
		std::int16_t MaxHeight = 0;
		Data::iterate(mChildren, MaxHeightFunctorT{MaxHeight});
		return MaxHeight;
	}

	struct DelegateMouseFunctorT
	{
		std::int16_t X;
		std::int16_t Y;

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

	void delegateMouse(std::int16_t X, std::int16_t Y)
	{
		Data::iterateUntil(mChildren, DelegateMouseFunctorT{X, Y});
	}

	// Container
	void releaseMouse(std::int16_t X, std::int16_t Y) final
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
		std::int16_t Right;

		template<typename T>
		void operator()(T & Child)
		{
			Child.resizeWidth(Right);
		}
	};

	void resizeWidth(std::int16_t X)
	{
		Data::iterate(mChildren, ResizeWidthFunctorT{X});
	}

	struct ResizeHeightFunctorT
	{
		std::int16_t Bottom;
		std::int16_t BoxHeight;
		std::int16_t Mod;
		std::int16_t Direction;

		template<typename T>
		void operator()(T & Child)
		{
			std::int16_t Height = BoxHeight;
			if (Mod > 0)
			{
				Height += Direction;
				--Mod;
			}
			Child.moveY(Bottom - Child.getBottom());
			Child.resizeHeight(Bottom + Height - Child.getTop());
			Bottom += Height;
		}
	};

	void resizeHeight(std::int16_t Y)
	{
		std::int16_t Height = getTop() + Y - getBottom();
		std::int16_t BoxHeight = Height / mSize;
		std::int16_t Mod;
		std::int16_t Direction;
		if (Height >= 0)
		{
			Mod = Height % mSize;
			Direction = 1;
		}
		else
		{
			Mod = -Height % mSize;
			Direction = -1;
		}
		Data::iterate(mChildren, ResizeHeightFunctorT{getBottom(), BoxHeight, Mod, Direction});
	}

	std::int16_t getBaseWidth() const
	{
		std::int16_t MaxWidth = 0;
		Data::iterate(mChildren, MaxWidthFunctorT{MaxWidth});
		return MaxWidth;
	}

	std::int16_t getBaseHeight() const
	{
		std::int16_t MaxHeight = 0;
		Data::iterate(mChildren, MaxHeightFunctorT{MaxHeight});
		return MaxHeight * mSize;
	}

	struct DelegateMouseFunctorT
	{
		std::int16_t X;
		std::int16_t Y;

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

	void delegateMouse(std::int16_t X, std::int16_t Y)
	{
		Data::iterateUntil(mChildren, DelegateMouseFunctorT{X, Y});
	}

	// Container
	void releaseMouse(std::int16_t X, std::int16_t Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent->releaseMouse(X, Y);
	}
};

}
}
