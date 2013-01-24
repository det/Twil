#pragma once

#include "Container.hpp"
#include "Widget.hpp"
#include "WindowBase.hpp"

#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

/// \brief Functionality shared by all split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxBaseT :
	public ContainerT,
	public WidgetT
{
	protected:
	ContainerT & mParent;
	FirstT mFirst;
	SecondT mSecond;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mRight = 0;
	signed short mTop = 0;
	signed short mClipLeft = 0;
	signed short mClipRight = 0;
	signed short mClipBottom = 0;
	signed short mClipTop = 0;

	/// \returns true if the position is within our bounds.
	bool checkThisContains(signed short X, signed short Y)
	{
		return X >= mLeft && X <= mRight && Y >= mBottom && Y <= mTop;
	}

	public:
	// SplitBox
	SplitBoxBaseT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mFirst{*this, Window, Theme},
		mSecond{*this, Window, Theme}
	{}

	/// \returns a reference to the first child.
	FirstT & getFirst()
	{
		return mFirst;
	}

	/// \returns a const reference to the first child.
	FirstT const & getFirst() const
	{
		return mFirst;
	}

	/// \returns a reference to the second child.
	SecondT & getSecond()
	{
		return mSecond;
	}

	/// \returns a const reference to the second child.
	SecondT const & getSecond() const
	{
		return mSecond;
	}

	// Widget
	void moveX(signed short X) final
	{
		mLeft += X;
		mRight += X;
		mClipLeft += X;
		mClipRight += X;
		mFirst.moveX(X);
		mSecond.moveX(X);
	}

	void moveY(signed short Y) final
	{
		mBottom += Y;
		mTop += Y;
		mClipBottom += Y;
		mClipTop += Y;
		mFirst.moveY(Y);
		mSecond.moveY(Y);
	}

	void draw() const final
	{
		mFirst.draw();
		mSecond.draw();
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
};

/// \brief Functionality shared by all horizontal split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxHorizontalT :
	public SplitBoxBaseT<FirstT, SecondT>
{
	protected:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::mLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mRight;
	using SplitBoxBaseT<FirstT, SecondT>::mTop;
	using SplitBoxBaseT<FirstT, SecondT>::mClipLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mClipRight;
	using SplitBoxBaseT<FirstT, SecondT>::mClipBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mClipTop;
	using SplitBoxBaseT<FirstT, SecondT>::checkThisContains;

	public:
	// SplitBox
	SplitBoxHorizontalT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		SplitBoxBaseT<FirstT, SecondT>{Parent, Window, Theme}
	{}

	// Widget
	void resizeHeight(signed short Y) final
	{
		mTop += Y;
		mClipTop += Y;
		mFirst.resizeHeight(Y);
		mSecond.resizeHeight(Y);
	}

	void setClipBottom(signed short Y) final
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(Y);
	}

	void setClipTop(signed short Y) final
	{
		mFirst.setClipTop(Y);
		mSecond.setClipTop(Y);
	}

	signed short getBaseWidth() const final
	{
		return mFirst.getBaseWidth() + mSecond.getBaseWidth();
	}

	signed short getBaseHeight() const final
	{
		return std::max(mFirst.getBaseHeight(), mSecond.getBaseHeight());
	}

	void delegateMouse(signed short X, signed short Y) final
	{
		if (X < mSecond.getLeft()) mFirst.delegateMouse(X, Y);
		else mSecond.delegateMouse(X, Y);
	}

	// Container
	void releaseMouse(signed short X, signed short Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent.releaseMouse(X, Y);
	}

	void handleChildBaseHeightChanged(void *) final
	{}
};

/// \brief Functionality shared by all vertical split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxVerticalT :
	public SplitBoxBaseT<FirstT, SecondT>
{
	protected:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::mLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mRight;
	using SplitBoxBaseT<FirstT, SecondT>::mTop;
	using SplitBoxBaseT<FirstT, SecondT>::mClipLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mClipRight;
	using SplitBoxBaseT<FirstT, SecondT>::mClipBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mClipTop;
	using SplitBoxBaseT<FirstT, SecondT>::checkThisContains;

	public:
	// SplitBox
	SplitBoxVerticalT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		SplitBoxBaseT<FirstT, SecondT>{Parent, Window, Theme}
	{}

	// Widget
	void resizeWidth(signed short X) final
	{
		mRight += X;
		mClipRight += X;
		mFirst.resizeWidth(X);
		mSecond.resizeWidth(X);
	}

	void setClipLeft(signed short X) final
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(X);
	}

	void setClipRight(signed short X) final
	{
		mFirst.setClipRight(X);
		mSecond.setClipRight(X);
	}

	signed short getBaseWidth() const final
	{
		return std::max(mFirst.getBaseWidth(), mSecond.getBaseWidth());
	}

	signed short getBaseHeight() const final
	{
		return mFirst.getBaseHeight() + mSecond.getBaseHeight();
	}

	void delegateMouse(signed short X, signed short Y) final
	{
		if (Y < mSecond.getBottom()) mFirst.delegateMouse(X, Y);
		else mSecond.delegateMouse(X, Y);
	}

	// Container
	void releaseMouse(signed short X, signed short Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent.releaseMouse(X, Y);
	}

	void handleChildBaseWidthChanged(void *) final
	{}
};

template<bool IsHorizontal, bool IsFirstStatic, typename FirstT, typename SecondT>
class SplitBoxT;

/// \brief A horizontal split box where the first child is fixed width.
///
/// Both children share the parent's height.
/// The first child is kept at its base width and clipped if neccesary.
/// The second child has its width set to any remaining space.
template<typename FirstT, typename SecondT>
class SplitBoxT<true, true, FirstT, SecondT> :
	public SplitBoxHorizontalT<FirstT, SecondT>
{
	private:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::mLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mRight;
	using SplitBoxBaseT<FirstT, SecondT>::mTop;
	using SplitBoxBaseT<FirstT, SecondT>::mClipLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mClipRight;
	using SplitBoxBaseT<FirstT, SecondT>::mClipBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mClipTop;

	void layout()
	{
		signed short Delta = mFirst.getLeft() + mFirst.getBaseWidth() - mFirst.getRight();
		mFirst.resizeWidth(Delta);
		mSecond.moveX(Delta);
		mSecond.resizeWidth(-Delta);
		mFirst.setClipRight(std::min(mRight, mClipRight));
	}

	public:
	// SplitBox
	SplitBoxT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		SplitBoxHorizontalT<FirstT, SecondT>{Parent, Window, Theme}
	{
		layout();
	}

	// Widget
	void resizeWidth(signed short X) final
	{
		mRight += X;
		mClipRight += X;
		mSecond.resizeWidth(X);
		mFirst.setClipRight(std::min(mRight, mClipRight));
	}

	void setClipLeft(signed short X) final
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(X);
	}

	void setClipRight(signed short X) final
	{
		mFirst.setClipRight(std::min(mRight, mClipRight));
		mSecond.setClipRight(X);
	}

	// Container
	void handleChildBaseWidthChanged(void * Child) final
	{
		if (Child == &mFirst) layout();
	}
};

/// \brief A horizontal split box where the second child is fixed width.
///
/// Both children share the parent's height.
/// The second child is kept at its base width and clipped if neccesary.
/// The first child has its width set to any remaining space.

template<typename FirstT, typename SecondT>
class SplitBoxT<true, false, FirstT, SecondT> :
	public SplitBoxHorizontalT<FirstT, SecondT>
{
	private:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::mLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mRight;
	using SplitBoxBaseT<FirstT, SecondT>::mTop;
	using SplitBoxBaseT<FirstT, SecondT>::mClipLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mClipRight;
	using SplitBoxBaseT<FirstT, SecondT>::mClipBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mClipTop;

	void layout()
	{
		signed short Delta = mSecond.getLeft() + mSecond.getBaseWidth() - mSecond.getRight();
		mFirst.resizeWidth(-Delta);
		mSecond.moveX(-Delta);
		mSecond.resizeWidth(Delta);
		mSecond.setClipLeft(std::max(mLeft, mClipLeft));
	}

	public:
	// SplitBox
	SplitBoxT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		SplitBoxHorizontalT<FirstT, SecondT>{Parent, Window, Theme}
	{
		layout();
	}

	// Widget
	void resizeWidth(signed short X) final
	{
		mRight += X;
		mClipRight += X;
		mFirst.resizeWidth(X);
		mSecond.moveX(X);
		mSecond.setClipLeft(std::max(mLeft, mClipLeft));
	}

	void setClipLeft(signed short X) final
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(std::max(mLeft, mClipLeft));
	}

	void setClipRight(signed short X) final
	{
		mFirst.setClipRight(X);
		mSecond.setClipRight(X);
	}

	// Container
	void handleChildBaseWidthChanged(void * Child) final
	{
		if (Child == &mSecond) layout();
	}
};

/// \brief A vertical split box where the first child is fixed height.
///
/// Both children share the parent's width.
/// The first child is kept at its base height and clipped if neccesary.
/// The second child has its height set to any remaining space.

template<typename FirstT, typename SecondT>
class SplitBoxT<false, true, FirstT, SecondT> :
	public SplitBoxVerticalT<FirstT, SecondT>
{
	private:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::mLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mRight;
	using SplitBoxBaseT<FirstT, SecondT>::mTop;
	using SplitBoxBaseT<FirstT, SecondT>::mClipLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mClipRight;
	using SplitBoxBaseT<FirstT, SecondT>::mClipBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mClipTop;

	void layout()
	{
		signed short Delta = mFirst.getBottom() + mFirst.getBaseHeight() - mFirst.getTop();
		mFirst.resizeHeight(Delta);
		mSecond.moveY(Delta);
		mSecond.resizeHeight(-Delta);
		mFirst.setClipTop(std::min(mTop, mClipTop));
	}

	public:
	// SplitBox
	SplitBoxT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		SplitBoxVerticalT<FirstT, SecondT>{Parent, Window, Theme}
	{
		layout();
	}

	// Widget
	void resizeHeight(signed short Y) final
	{
		mTop += Y;
		mClipTop += Y;
		mSecond.resizeHeight(Y);
		mFirst.setClipTop(std::min(mTop, mClipTop));
	}

	void setClipBottom(signed short Y) final
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(Y);
	}

	void setClipTop(signed short Y) final
	{
		mFirst.setClipTop(std::min(mTop, mClipTop));
		mSecond.setClipTop(Y);
	}

	// Container
	void handleChildBaseHeightChanged(void * Child) final
	{
		if (Child == &mFirst) layout();
	}
};

/// \brief A vertical split box where the second child is fixed height.
///
/// Both children share the parent's width.
/// The second child is kept at its base height and clipped if neccesary.
/// The first child has its height set to any remaining space.

template<typename FirstT, typename SecondT>
class SplitBoxT<false, false, FirstT, SecondT> :
	public SplitBoxVerticalT<FirstT, SecondT>
{
	private:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::mLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mRight;
	using SplitBoxBaseT<FirstT, SecondT>::mTop;
	using SplitBoxBaseT<FirstT, SecondT>::mClipLeft;
	using SplitBoxBaseT<FirstT, SecondT>::mClipRight;
	using SplitBoxBaseT<FirstT, SecondT>::mClipBottom;
	using SplitBoxBaseT<FirstT, SecondT>::mClipTop;

	void layout()
	{
		signed short Delta = mSecond.getBottom() + mSecond.getBaseHeight() - mSecond.getTop();
		mFirst.resizeHeight(-Delta);
		mSecond.moveY(-Delta);
		mSecond.resizeHeight(Delta);
		mSecond.setClipBottom(std::max(mBottom, mClipBottom));
	}

	public:
	// SplitBox
	SplitBoxT(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Theme) :
		SplitBoxVerticalT<FirstT, SecondT>{Parent, Window, Theme}
	{
		layout();
	}

	// Widget
	void resizeHeight(signed short Y) final
	{
		mTop += Y;
		mClipTop += Y;
		mFirst.resizeHeight(Y);
		mSecond.moveY(Y);
		mSecond.setClipBottom(std::max(mBottom, mClipBottom));
	}

	void setClipBottom(signed short Y) final
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(std::max(mBottom, mClipBottom));
	}

	void setClipTop(signed short Y) final
	{
		mFirst.setClipTop(Y);
		mSecond.setClipTop(Y);
	}

	// Container
	void handleChildBaseHeightChanged(void * Child) final
	{
		if (Child == &mSecond) layout();
	}
};

}
}
