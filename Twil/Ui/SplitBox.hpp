#pragma once

#include "Container.hpp"
#include "WindowBase.hpp"

namespace Twil {
namespace Ui {

/// \brief Functionality shared by all split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxBaseT
:
	public ContainerT
{
	SplitBoxBaseT(SplitBoxBaseT const &) = delete;
	SplitBoxBaseT & operator =(SplitBoxBaseT const &) = delete;

protected:
	ContainerT * mParent;
	FirstT mFirst;
	SecondT mSecond;

	std::int16_t getMouseLeft() const
	{
		return std::max<std::int16_t>(getLeft(), getClipLeft());
	}

	std::int16_t getMouseRight() const
	{
		return std::min<std::int16_t>(getRight(), getClipRight());
	}

	std::int16_t getMouseBottom() const
	{
		return std::max<std::int16_t>(getBottom(), getClipBottom());
	}

	std::int16_t getMouseTop() const
	{
		return std::min<std::int16_t>(getTop(), getClipTop());
	}

	bool checkThisContains(std::int16_t X, std::int16_t Y) const
	{
		return (
			X >= getMouseLeft() && X >= getClipLeft() &&
			X <= getMouseRight() && X <= getClipRight() &&
			Y >= getMouseBottom() && Y >= getClipBottom() &&
			Y <= getMouseTop() && Y <= getClipTop());
	}

public:
	// SplitBox
	SplitBoxBaseT() = default;

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		mFirst.init(*this, Window);
		mSecond.init(*this, Window);
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
	void moveX(std::int16_t X)
	{
		mFirst.moveX(X);
		mSecond.moveX(X);
	}

	void moveY(std::int16_t Y)
	{
		mFirst.moveY(Y);
		mSecond.moveY(Y);
	}

	std::int16_t getLeft() const
	{
		return mFirst.getLeft();
	}

	std::int16_t getBottom() const
	{
		return mFirst.getBottom();
	}

	std::int16_t getRight() const
	{
		return mSecond.getRight();
	}

	std::int16_t getTop() const
	{
		return mSecond.getTop();
	}

	std::int16_t getClipLeft() const
	{
		return mFirst.getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return mFirst.getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return mSecond.getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return mSecond.getClipTop();
	}
};

/// \brief Functionality shared by all horizontal split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxHorizontalT
:
	public SplitBoxBaseT<FirstT, SecondT>
{
protected:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::checkThisContains;

public:
	// Widget
	void resizeHeight(std::int16_t Y)
	{
		mFirst.resizeHeight(Y);
		mSecond.resizeHeight(Y);
	}

	void setClipBottom(std::int16_t Y)
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(Y);
	}

	void setClipTop(std::int16_t Y)
	{
		mFirst.setClipTop(Y);
		mSecond.setClipTop(Y);
	}

	std::int16_t getBaseWidth() const
	{
		return mFirst.getBaseWidth() + mSecond.getBaseWidth();
	}

	std::int16_t getBaseHeight() const
	{
		return std::max(mFirst.getBaseHeight(), mSecond.getBaseHeight());
	}

	void delegateMouse(std::int16_t X, std::int16_t Y)
	{
		if (X < mSecond.getLeft()) mFirst.delegateMouse(X, Y);
		else mSecond.delegateMouse(X, Y);
	}

	// Container
	void releaseMouse(std::int16_t X, std::int16_t Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent->releaseMouse(X, Y);
	}

	void handleChildBaseHeightChanged(void *) final
	{
		mParent->handleChildBaseHeightChanged(this);
	}
};

/// \brief Functionality shared by all vertical split boxes.
template<typename FirstT, typename SecondT>
class SplitBoxVerticalT
:
	public SplitBoxBaseT<FirstT, SecondT>
{
protected:
	using SplitBoxBaseT<FirstT, SecondT>::mParent;
	using SplitBoxBaseT<FirstT, SecondT>::mFirst;
	using SplitBoxBaseT<FirstT, SecondT>::mSecond;
	using SplitBoxBaseT<FirstT, SecondT>::checkThisContains;

public:
	// Widget
	void resizeWidth(std::int16_t X)
	{
		mFirst.resizeWidth(X);
		mSecond.resizeWidth(X);
	}

	void setClipLeft(std::int16_t X)
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(X);
	}

	void setClipRight(std::int16_t X)
	{
		mFirst.setClipRight(X);
		mSecond.setClipRight(X);
	}

	std::int16_t getBaseWidth() const
	{
		return std::max(mFirst.getBaseWidth(), mSecond.getBaseWidth());
	}

	std::int16_t getBaseHeight() const
	{
		return mFirst.getBaseHeight() + mSecond.getBaseHeight();
	}

	void delegateMouse(std::int16_t X, std::int16_t Y)
	{
		if (Y < mSecond.getBottom()) mFirst.delegateMouse(X, Y);
		else mSecond.delegateMouse(X, Y);
	}

	// Container
	void releaseMouse(std::int16_t X, std::int16_t Y) final
	{
		if (checkThisContains(X, Y)) delegateMouse(X, Y);
		else mParent->releaseMouse(X, Y);
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
class SplitBoxT<true, true, FirstT, SecondT>
:
	public SplitBoxHorizontalT<FirstT, SecondT>
{
protected:
	using SplitBoxHorizontalT<FirstT, SecondT>::mParent;
	using SplitBoxHorizontalT<FirstT, SecondT>::mFirst;
	using SplitBoxHorizontalT<FirstT, SecondT>::mSecond;
	using SplitBoxHorizontalT<FirstT, SecondT>::getMouseRight;

	void layout()
	{
		std::int16_t Delta = mFirst.getLeft() + mFirst.getBaseWidth() - mFirst.getRight();
		mFirst.resizeWidth(Delta);
		mSecond.moveX(Delta);
		mSecond.resizeWidth(-Delta);
		mFirst.setClipRight(getMouseRight());
	}

public:
	// SplitBox
	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		SplitBoxHorizontalT<FirstT, SecondT>::init(Parent, Window);
		layout();
	}

	// Widget
	void resizeWidth(std::int16_t X)
	{
		mSecond.resizeWidth(X);
		mFirst.setClipRight(getMouseRight());
	}

	void setClipLeft(std::int16_t X)
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(X);
	}

	void setClipRight(std::int16_t X)
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
class SplitBoxT<true, false, FirstT, SecondT>
:
	public SplitBoxHorizontalT<FirstT, SecondT>
{
protected:
	using SplitBoxHorizontalT<FirstT, SecondT>::mParent;
	using SplitBoxHorizontalT<FirstT, SecondT>::mFirst;
	using SplitBoxHorizontalT<FirstT, SecondT>::mSecond;
	using SplitBoxHorizontalT<FirstT, SecondT>::getMouseLeft;

	void layout()
	{
		std::int16_t Delta = mSecond.getLeft() + mSecond.getBaseWidth() - mSecond.getRight();
		mFirst.resizeWidth(-Delta);
		mSecond.moveX(-Delta);
		mSecond.resizeWidth(Delta);
		mSecond.setClipLeft(getMouseLeft());
	}

public:
	// SplitBox
	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		SplitBoxHorizontalT<FirstT, SecondT>::init(Parent, Window);
		layout();
	}

	// Widget
	void resizeWidth(std::int16_t X)
	{
		mFirst.resizeWidth(X);
		mSecond.moveX(X);
		mSecond.setClipLeft(getMouseLeft());
	}

	void setClipLeft(std::int16_t X)
	{
		mFirst.setClipLeft(X);
		mSecond.setClipLeft(getMouseLeft());
	}

	void setClipRight(std::int16_t X)
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
class SplitBoxT<false, true, FirstT, SecondT>
:
	public SplitBoxVerticalT<FirstT, SecondT>
{
protected:
	using SplitBoxVerticalT<FirstT, SecondT>::mParent;
	using SplitBoxVerticalT<FirstT, SecondT>::mFirst;
	using SplitBoxVerticalT<FirstT, SecondT>::mSecond;
	using SplitBoxVerticalT<FirstT, SecondT>::getMouseTop;

	void layout()
	{
		std::int16_t Delta = mFirst.getBottom() + mFirst.getBaseHeight() - mFirst.getTop();
		mFirst.resizeHeight(Delta);
		mSecond.moveY(Delta);
		mSecond.resizeHeight(-Delta);
		mFirst.setClipTop(getMouseTop());
	}

public:
	// SplitBox
	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		SplitBoxVerticalT<FirstT, SecondT>::init(Parent, Window);
		layout();
	}

	// Widget
	void resizeHeight(std::int16_t Y)
	{
		mSecond.resizeHeight(Y);
		mFirst.setClipTop(getMouseTop());
	}

	void setClipBottom(std::int16_t Y)
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(Y);
	}

	void setClipTop(std::int16_t Y)
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
class SplitBoxT<false, false, FirstT, SecondT>
:
	public SplitBoxVerticalT<FirstT, SecondT>
{
protected:
	using SplitBoxVerticalT<FirstT, SecondT>::mParent;
	using SplitBoxVerticalT<FirstT, SecondT>::mFirst;
	using SplitBoxVerticalT<FirstT, SecondT>::mSecond;
	using SplitBoxVerticalT<FirstT, SecondT>::getMouseBottom;

	void layout()
	{
		std::int16_t Delta = mSecond.getBottom() + mSecond.getBaseHeight() - mSecond.getTop();
		mFirst.resizeHeight(-Delta);
		mSecond.moveY(-Delta);
		mSecond.resizeHeight(Delta);
		mSecond.setClipBottom(getMouseBottom());
	}

public:
	// SplitBox
	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		SplitBoxVerticalT<FirstT, SecondT>::init(Parent, Window);
		layout();
	}

	// Widget
	void resizeHeight(std::int16_t Y)
	{
		mFirst.resizeHeight(Y);
		mSecond.moveY(Y);
		mSecond.setClipBottom(getMouseBottom());
	}

	void setClipBottom(std::int16_t Y)
	{
		mFirst.setClipBottom(Y);
		mSecond.setClipBottom(getMouseBottom());
	}

	void setClipTop(std::int16_t Y)
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
