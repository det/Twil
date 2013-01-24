#pragma once

#include "Container.hpp"
#include "Tuple.hpp"
#include "Widget.hpp"

#include <algorithm>

namespace Twil {

namespace Theme {
class ManagerT;
}

namespace Ui {

class WindowBaseT;

/// \brief Functionality shared by both horizontal and vertical partition boxes.
template<typename ... ArgsT>
class PartitionBoxBaseT :
	public ContainerT,
	public WidgetT
{
	protected:
	ContainerT & mParent;
	TupleT<ArgsT ...> mChildren;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mRight = 0;
	signed short mTop = 0;

	static signed short const mSize = static_cast<signed short>(sizeof ... (ArgsT));

	bool checkThisContains(signed short X, signed short Y)
	{
		return X >= mLeft && X <= mRight && Y >= mBottom && Y <= mTop;
	}

	public:
	// PartitionBoxBase
	PartitionBoxBaseT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mChildren{*this, Window, Theme}
	{}

	/// \returns A reference to a child widget.
	///
	/// \param I Index of the child
	template<std::size_t I>
	typename TupleElementT<I, ArgsT ...>::ElementT & getChild()
	{
		return TupleElementT<I, ArgsT ...>().get(mChildren);
	}

	/// \returns A const reference to a child widget.
	///
	/// \param I Index of the child
	template<std::size_t I>
	typename TupleElementT<I, ArgsT ...>::ElementT const & getChild() const
	{
		return TupleElementT<I, ArgsT ...>().get(mChildren);
	}

	// Widget
	struct MoveXFunctorT
	{
		signed short X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveX(X);
		}
	};

	void moveX(signed short X) final
	{
		mLeft += X;
		mRight += X;
		mChildren.iterate(MoveXFunctorT{X});
	}

	struct MoveYFunctorT
	{
		signed short Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.moveY(Y);
		}
	};

	void moveY(signed short Y) final
	{
		mBottom += Y;
		mTop += Y;
		mChildren.iterate(MoveYFunctorT{Y});
	}

	struct SetClipLeftFunctorT
	{
		signed short X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipLeft(X);
		}
	};

	void setClipLeft(signed short X) final
	{
		mChildren.iterate(SetClipLeftFunctorT{X});
	}

	struct SetClipBottomFunctorT
	{
		signed short Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipBottom(Y);
		}
	};

	void setClipBottom(signed short Y) final
	{
		mChildren.iterate(SetClipBottomFunctorT{Y});
	}

	struct SetClipRightFunctorT
	{
		signed short X;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipRight(X);
		}
	};

	void setClipRight(signed short X) final
	{
		mChildren.iterate(SetClipRightFunctorT{X});
	}

	struct SetClipTopFunctorT
	{
		signed short Y;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setClipTop(Y);
		}
	};

	void setClipTop(signed short Y) final
	{
		mChildren.iterate(SetClipTopFunctorT{Y});
	}

	struct DrawFunctorT
	{
		template<typename T>
		void operator()(T const & Child)
		{
			Child.draw();
		}
	};

	void draw() const final
	{
		mChildren.iterate(DrawFunctorT{});
	}

	signed short getLeft() const final
	{
		return mLeft;
	}

	signed short getBottom() const final
	{
		return mBottom;
	}

	signed short getRight() const final
	{
		return mRight;
	}

	signed short getTop() const final
	{
		return mTop;
	}

	struct MaxWidthFunctorT
	{
		signed short & MaxWidth;

		template<typename T>
		void operator()(T const & Child)
		{
			MaxWidth = std::max(MaxWidth, Child.getBaseWidth());
		}
	};

	struct MaxHeightFunctorT
	{
		signed short & MaxHeight;

		template<typename T>
		void operator()(T const & Child)
		{
			MaxHeight = std::max(MaxHeight, Child.getBaseHeight());
		}
	};

	// Container
	void handleChildBaseWidthChanged(void *) final
	{
		mParent.handleChildBaseWidthChanged(this);
	}

	void handleChildBaseHeightChanged(void *) final
	{
		mParent.handleChildBaseHeightChanged(this);
	}
};

template<bool IsHorizontal, typename ... ArgsT>
class PartitionBoxT;

/// \brief A horizontal partition box.
///
/// All children Share the parent's height. The width is split evenly among the children.
///
/// \param ArgsT A template argument pack of children widget types.

template<typename ... ArgsT>
class PartitionBoxT<true, ArgsT ...> :
	public PartitionBoxBaseT<ArgsT ...>
{
	private:
	using PartitionBoxBaseT<ArgsT ...>::mParent;
	using PartitionBoxBaseT<ArgsT ...>::mChildren;
	using PartitionBoxBaseT<ArgsT ...>::mLeft;
	using PartitionBoxBaseT<ArgsT ...>::mBottom;
	using PartitionBoxBaseT<ArgsT ...>::mRight;
	using PartitionBoxBaseT<ArgsT ...>::mTop;
	using PartitionBoxBaseT<ArgsT ...>::mSize;
	using PartitionBoxBaseT<ArgsT ...>::checkThisContains;
	using typename PartitionBoxBaseT<ArgsT ...>::MaxWidthFunctorT;
	using typename PartitionBoxBaseT<ArgsT ...>::MaxHeightFunctorT;

	public:
	// PartitionBox
	PartitionBoxT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		PartitionBoxBaseT<ArgsT ...>{Parent, Window, Theme}
	{}

	// Widget
	struct ResizeWidthFunctorT
	{
		signed short Left;
		signed short BoxWidth;
		signed short Mod;

		template<typename T>
		void operator()(T & Child)
		{
			signed short Width = BoxWidth;
			if (Mod > 0) {
				++Width;
				--Mod;
			}
			Child.moveX(Left - Child.getLeft());
			Child.resizeWidth(Left + Width - Child.getRight());
			Left += Width;
		}
	};

	void resizeWidth(signed short X) final
	{
		mRight += X;
		signed short Width = mRight - mLeft;
		signed short BoxWidth = Width / mSize;
		signed short Mod = Width % mSize;
		mChildren.iterate(ResizeWidthFunctorT{mLeft, BoxWidth, Mod});
	}

	struct ResizeHeightFunctorT
	{
		signed short Top;

		template<typename T>
		void operator()(T & Child)
		{
			Child.resizeHeight(Top);
		}
	};

	void resizeHeight(signed short Y) final
	{
		mTop += Y;
		mChildren.iterate(ResizeHeightFunctorT{Y});
	}

	signed short getBaseWidth() const final
	{
		signed short MaxWidth = 0;
		mChildren.iterate(MaxWidthFunctorT{MaxWidth});
		return MaxWidth * mSize;
	}

	signed short getBaseHeight() const final
	{
		signed short MaxHeight = 0;
		mChildren.iterate(MaxHeightFunctorT{MaxHeight});
		return MaxHeight;
	}

	struct DelegateMouseFunctorT
	{
		signed short X;
		signed short Y;

		template<typename T>
		bool operator()(T & Child)
		{
			if (X < Child.getRight()) {
				Child.delegateMouse(X, Y);
				return false;
			}
			return true;
		}
	};

	void delegateMouse(signed short X, signed short Y) final
	{
		mChildren.iterateUntil(DelegateMouseFunctorT{X, Y});
	}

	// Container
	void releaseMouse(signed short X, signed short Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent.releaseMouse(X, Y);
	}

};

/// \brief A vertical partition box.
///
/// All children Share the parent's width. The height is split evenly among the children.
///
/// \param ArgsT A template argument pack of children widget types.

template<typename ... ArgsT>
class PartitionBoxT<false, ArgsT ...> :
	public PartitionBoxBaseT<ArgsT ...>
{
	private:
	using PartitionBoxBaseT<ArgsT ...>::mParent;
	using PartitionBoxBaseT<ArgsT ...>::mChildren;
	using PartitionBoxBaseT<ArgsT ...>::mLeft;
	using PartitionBoxBaseT<ArgsT ...>::mBottom;
	using PartitionBoxBaseT<ArgsT ...>::mRight;
	using PartitionBoxBaseT<ArgsT ...>::mTop;
	using PartitionBoxBaseT<ArgsT ...>::mSize;
	using PartitionBoxBaseT<ArgsT ...>::checkThisContains;
	using typename PartitionBoxBaseT<ArgsT ...>::MaxWidthFunctorT;
	using typename PartitionBoxBaseT<ArgsT ...>::MaxHeightFunctorT;

	public:
	// PartitionBox
	PartitionBoxT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		PartitionBoxBaseT<ArgsT ...>{Parent, Window, Theme}
	{}

	// Widget
	struct ResizeWidthFunctorT
	{
		signed short Right;

		template<typename T>
		void operator()(T & Child)
		{
			Child.resizeWidth(Right);
		}
	};

	void resizeWidth(signed short X) final
	{
		mRight += X;
		mChildren.iterate(ResizeWidthFunctorT{X});
	}

	struct ResizeHeightFunctorT
	{
		signed short Bottom;
		signed short BoxHeight;
		signed short Mod;

		template<typename T>
		void operator()(T & Child)
		{
			signed short Height = BoxHeight;
			if (Mod > 0) {
				++Height;
				--Mod;
			}
			Child.moveY(Bottom - Child.getBottom());
			Child.resizeHeight(Bottom + Height - Child.getTop());
			Bottom += Height;
		}
	};

	void resizeHeight(signed short Y) final
	{
		mTop += Y;
		signed short Height = mTop - mBottom;
		signed short BoxHeight = Height / mSize;
		signed short Mod = Height % mSize;
		mChildren.iterate(ResizeHeightFunctorT{mBottom, BoxHeight, Mod});
	}

	signed short getBaseWidth() const final
	{
		signed short MaxWidth = 0;
		mChildren.iterate(MaxWidthFunctorT{MaxWidth});
		return MaxWidth;
	}

	signed short getBaseHeight() const final
	{
		signed short MaxHeight = 0;
		mChildren.iterate(MaxHeightFunctorT{MaxHeight});
		return MaxHeight * mSize;
	}

	struct DelegateMouseFunctorT
	{
		signed short X;
		signed short Y;

		template<typename T>
		bool operator()(T & Child)
		{
			if (Y < Child.getTop()) {
				Child.delegateMouse(X, Y);
				return false;
			}
			return true;
		}
	};

	void delegateMouse(signed short X, signed short Y) final
	{
		mChildren.iterateUntil(DelegateMouseFunctorT{X, Y});
	}

	// Container
	void releaseMouse(signed short X, signed short Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent.releaseMouse(X, Y);
	}
};

}
}
