#pragma once

#include "Container.hpp"
#include "MouseManager.hpp"
#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

/// \brief Functionality shared by all split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxBaseT :
	public ContainerT
{
	protected:
	ContainerT * mParent;
	FirstT mFirst;
	SecondT mSecond;

	signed short getMouseLeft() const
	{
		return std::max<signed short>(getLeft(), getClipLeft());
	}

	signed short getMouseRight() const
	{
		return std::min<signed short>(getRight(), getClipRight());
	}

	signed short getMouseBottom() const
	{
		return std::max<signed short>(getBottom(), getClipBottom());
	}

	signed short getMouseTop() const
	{
		return std::min<signed short>(getTop(), getClipTop());
	}

	bool checkThisContains(signed short X, signed short Y) const
	{
		return (
			X >= getMouseLeft() && X >= getClipLeft() &&
			X <= getMouseRight() && X <= getClipRight() &&
			Y >= getMouseBottom() && Y >= getClipBottom() &&
			Y <= getMouseTop() && Y <= getClipTop()
		);
	}

	public:
	// SplitBox
	void init(ContainerT & Parent, Theme::ManagerT & ThemeManager)
	{
		mParent = &Parent;
		mFirst.init(*this, ThemeManager);
		mSecond.init(*this, ThemeManager);
	}

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
	void moveX(signed short X)
	{
		mFirst.moveX(X);
		mSecond.moveX(X);
	}

	void moveY(signed short Y)
	{
		mFirst.moveY(Y);
		mSecond.moveY(Y);
	}

	signed short getLeft() const
	{
		return mFirst.getLeft();
	}

	signed short getBottom() const
	{
		return mFirst.getBottom();
	}

	signed short getRight() const
	{
		return mSecond.getRight();
	}

	signed short getTop() const
	{
		return mSecond.getTop();
	}

	signed short getClipLeft() const
	{
		return mFirst.getClipLeft();
	}

	signed short getClipBottom() const
	{
		return mFirst.getClipBottom();
	}

	signed short getClipRight() const
	{
		return mSecond.getClipRight();
	}

	signed short getClipTop() const
	{
		return mSecond.getClipTop();
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
	using SplitBoxBaseT<FirstT, SecondT>::checkThisContains;

	public:
	// Widget
	void resizeHeight(signed short Y)
	{
		mFirst.resizeHeight(Y);
		mSecond.resizeHeight(Y);
	}

	void setClipBottom(signed short Y)
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(Y);
	}

	void setClipTop(signed short Y)
	{
		mFirst.setClipTop(Y);
		mSecond.setClipTop(Y);
	}

	signed short getBaseWidth() const
	{
		return mFirst.getBaseWidth() + mSecond.getBaseWidth();
	}

	signed short getBaseHeight() const
	{
		return std::max(mFirst.getBaseHeight(), mSecond.getBaseHeight());
	}

	void delegateMouse(MouseManagerT & MouseManager, signed short X, signed short Y)
	{
		if (X < mSecond.getLeft()) mFirst.delegateMouse(MouseManager, X, Y);
		else mSecond.delegateMouse(MouseManager, X, Y);
	}

	// Container
	void releaseMouse(MouseManagerT & MouseManager, signed short X, signed short Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(MouseManager, X, Y);
		else mParent->releaseMouse(MouseManager, X, Y);
	}

	void handleChildBaseHeightChanged(void *) final
	{
		mParent->handleChildBaseHeightChanged(this);
	}
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
	using SplitBoxBaseT<FirstT, SecondT>::checkThisContains;

	public:
	// Widget
	void resizeWidth(signed short X)
	{
		mFirst.resizeWidth(X);
		mSecond.resizeWidth(X);
	}

	void setClipLeft(signed short X)
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(X);
	}

	void setClipRight(signed short X)
	{
		mFirst.setClipRight(X);
		mSecond.setClipRight(X);
	}

	signed short getBaseWidth() const
	{
		return std::max(mFirst.getBaseWidth(), mSecond.getBaseWidth());
	}

	signed short getBaseHeight() const
	{
		return mFirst.getBaseHeight() + mSecond.getBaseHeight();
	}

	void delegateMouse(MouseManagerT & MouseManager, signed short X, signed short Y)
	{
		if (Y < mSecond.getBottom()) mFirst.delegateMouse(MouseManager, X, Y);
		else mSecond.delegateMouse(MouseManager, X, Y);
	}

	// Container
	void releaseMouse(MouseManagerT & MouseManager, signed short X, signed short Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(MouseManager, X, Y);
		else mParent->releaseMouse(MouseManager, X, Y);
	}

	void handleChildBaseWidthChanged(void *) final
	{
		mParent->handleChildBaseWidthChanged(this);
	}
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
	protected:
	using SplitBoxHorizontalT<FirstT, SecondT>::mParent;
	using SplitBoxHorizontalT<FirstT, SecondT>::mFirst;
	using SplitBoxHorizontalT<FirstT, SecondT>::mSecond;
	using SplitBoxHorizontalT<FirstT, SecondT>::getMouseRight;

	void layout()
	{
		signed short Delta = mFirst.getLeft() + mFirst.getBaseWidth() - mFirst.getRight();
		mFirst.resizeWidth(Delta);
		mSecond.moveX(Delta);
		mSecond.resizeWidth(-Delta);
		mFirst.setClipRight(getMouseRight());
	}

	public:
	// SplitBox
	void init(ContainerT & Parent, Theme::ManagerT & ThemeManager)
	{
		SplitBoxHorizontalT<FirstT, SecondT>::init(Parent, ThemeManager);
		layout();
	}

	// Widget
	void resizeWidth(signed short X)
	{
		mSecond.resizeWidth(X);
		mFirst.setClipRight(getMouseRight());
	}

	void setClipLeft(signed short X)
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(X);
	}

	void setClipRight(signed short X)
	{
		mFirst.setClipRight(getMouseRight());
		mSecond.setClipRight(X);
	}

	// Container
	void handleChildBaseWidthChanged(void * Child) final
	{
		if (Child == &mFirst) layout();
		mParent->handleChildBaseWidthChanged(this);
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
	protected:
	using SplitBoxHorizontalT<FirstT, SecondT>::mParent;
	using SplitBoxHorizontalT<FirstT, SecondT>::mFirst;
	using SplitBoxHorizontalT<FirstT, SecondT>::mSecond;
	using SplitBoxHorizontalT<FirstT, SecondT>::getMouseLeft;

	void layout()
	{
		signed short Delta = mSecond.getLeft() + mSecond.getBaseWidth() - mSecond.getRight();
		mFirst.resizeWidth(-Delta);
		mSecond.moveX(-Delta);
		mSecond.resizeWidth(Delta);
		mSecond.setClipLeft(getMouseLeft());
	}

	public:
	// SplitBox
	void init(ContainerT & Parent, Theme::ManagerT & ThemeManager)
	{
		SplitBoxHorizontalT<FirstT, SecondT>::init(Parent, ThemeManager);
		layout();
	}

	// Widget
	void resizeWidth(signed short X)
	{
		mFirst.resizeWidth(X);
		mSecond.moveX(X);
		mSecond.setClipLeft(getMouseLeft());
	}

	void setClipLeft(signed short X)
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(getMouseLeft());
	}

	void setClipRight(signed short X)
	{
		mFirst.setClipRight(X);
		mSecond.setClipRight(X);
	}

	// Container
	void handleChildBaseWidthChanged(void * Child) final
	{
		if (Child == &mSecond) layout();
		mParent->handleChildBaseWidthChanged(this);
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
	protected:
	using SplitBoxVerticalT<FirstT, SecondT>::mParent;
	using SplitBoxVerticalT<FirstT, SecondT>::mFirst;
	using SplitBoxVerticalT<FirstT, SecondT>::mSecond;
	using SplitBoxVerticalT<FirstT, SecondT>::getMouseTop;

	void layout()
	{
		signed short Delta = mFirst.getBottom() + mFirst.getBaseHeight() - mFirst.getTop();
		mFirst.resizeHeight(Delta);
		mSecond.moveY(Delta);
		mSecond.resizeHeight(-Delta);
		mFirst.setClipTop(getMouseTop());
	}

	public:
	// SplitBox
	void init(ContainerT & Parent, Theme::ManagerT & ThemeManager)
	{
		SplitBoxVerticalT<FirstT, SecondT>::init(Parent, ThemeManager);
		layout();
	}

	// Widget
	void resizeHeight(signed short Y)
	{
		mSecond.resizeHeight(Y);
		mFirst.setClipTop(getMouseTop());
	}

	void setClipBottom(signed short Y)
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(Y);
	}

	void setClipTop(signed short Y)
	{
		mFirst.setClipTop(getMouseTop());
		mSecond.setClipTop(Y);
	}

	// Container
	void handleChildBaseHeightChanged(void * Child) final
	{
		if (Child == &mFirst) layout();
		mParent->handleChildBaseHeightChanged(this);
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
	protected:
	using SplitBoxVerticalT<FirstT, SecondT>::mParent;
	using SplitBoxVerticalT<FirstT, SecondT>::mFirst;
	using SplitBoxVerticalT<FirstT, SecondT>::mSecond;
	using SplitBoxVerticalT<FirstT, SecondT>::getMouseBottom;

	void layout()
	{
		signed short Delta = mSecond.getBottom() + mSecond.getBaseHeight() - mSecond.getTop();
		mFirst.resizeHeight(-Delta);
		mSecond.moveY(-Delta);
		mSecond.resizeHeight(Delta);
		mSecond.setClipBottom(getMouseBottom());
	}

	public:
	// SplitBox
	void init(ContainerT & Parent, Theme::ManagerT & ThemeManager)
	{
		SplitBoxVerticalT<FirstT, SecondT>::init(Parent, ThemeManager);
		layout();
	}

	// Widget
	void resizeHeight(signed short Y)
	{
		mFirst.resizeHeight(Y);
		mSecond.moveY(Y);
		mSecond.setClipBottom(getMouseBottom());
	}

	void setClipBottom(signed short Y)
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(getMouseBottom());
	}

	void setClipTop(signed short Y)
	{
		mFirst.setClipTop(Y);
		mSecond.setClipTop(Y);
	}

	// Container
	void handleChildBaseHeightChanged(void * Child) final
	{
		if (Child == &mSecond) layout();
		mParent->handleChildBaseHeightChanged(this);
	}
};

}
}
