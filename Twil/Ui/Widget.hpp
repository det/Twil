#pragma once

#include "WidgetFwd.hpp"

#include "ContainerFwd.hpp"
#include "UnitFwd.hpp"
#include "WindowBaseFwd.hpp"

#include <cstdint>
#include <utility>

namespace Twil {
namespace Ui {

class WidgetT
{
public:
	virtual ~WidgetT() = default;

	/// \brief Initialize the widget
	virtual void init(ContainerT & Parent, WindowBaseT & Window) = 0;

	/// \brief Move the left and right position and clipping bounds.
	virtual void moveX(DipT Delta) = 0;

	/// \brief Move the bottom and top position and clipping bounds.
	virtual void moveY(DipT Delta) = 0;

	/// \brief Move the right position and clipping bound.
	virtual void resizeWidth(DipT Delta) = 0;

	/// \brief Move the top position and clipping bound.
	virtual void resizeHeight(DipT Delta) = 0;

	/// \brief Set the left clipping bound.
	virtual void setClipLeft(DipT Absolute) = 0;

	/// \brief Set the right clipping bound.
	virtual void setClipRight(DipT Absolute) = 0;

	/// \brief Set the bottom clipping bound.
	virtual void setClipBottom(DipT Absolute) = 0;

	/// \brief Set the top clipping bound.
	virtual void setClipTop(DipT Absolute) = 0;

	/// \returns The left position bound.
	virtual DipT getLeft() const = 0;

	/// \returns The bottom position bound.
	virtual DipT getBottom() const = 0;

	/// \returns The right position bound.
	virtual DipT getRight() const = 0;

	/// \returns The top position bound.
	virtual DipT getTop() const = 0;

	/// \returns The left clip line.
	virtual DipT getClipLeft() const = 0;

	/// \returns The right clip line.
	virtual DipT getClipRight() const = 0;

	/// \returns The bottom clip line.
	virtual DipT getClipBottom() const = 0;

	/// \returns The top clip line.
	virtual DipT getClipTop() const = 0;

	/// \returns The base width.
	virtual DipT getBaseWidth() const = 0;

	/// \returns The base height.
	virtual DipT getBaseHeight() const = 0;

	/// \brief Take control of the mouse or pass it to someone else.
	virtual void delegateMouse(DipT X, DipT Y) = 0;
};

template<typename T>
class WidgetModelT
:
	public WidgetT
{
private:
	T mData;

public:
	virtual void init(ContainerT & Parent, WindowBaseT & Window) final
	{
		mData.init(Parent, Window);
	}

	void moveX(DipT Delta) final
	{
		mData.moveX(Delta);
	}

	void moveY(DipT Delta) final
	{
		mData.moveY(Delta);
	}

	void resizeWidth(DipT Delta) final
	{
		mData.resizeWidth(Delta);
	}

	void resizeHeight(DipT Delta) final
	{
		mData.resizeHeight(Delta);
	}

	void setClipLeft(DipT Absolute) final
	{
		mData.setClipLeft(Absolute);
	}

	void setClipRight(DipT Absolute) final
	{
		mData.setClipRight(Absolute);
	}

	void setClipBottom(DipT Absolute) final
	{
		mData.setClipBottom(Absolute);
	}

	void setClipTop(DipT Absolute) final
	{
		mData.setClipTop(Absolute);
	}

	DipT getLeft() const final
	{
		return mData.getLeft();
	}

	DipT getBottom() const final
	{
		return mData.getBottom();
	}

	DipT getRight() const final
	{
		return mData.getRight();
	}

	DipT getTop() const final
	{
		return mData.getTop();
	}

	DipT getClipLeft() const final
	{
		return mData.getClipLeft();
	}

	DipT getClipRight() const final
	{
		return mData.getClipRight();
	}

	DipT getClipBottom() const final
	{
		return mData.getClipBottom();
	}

	DipT getClipTop() const final
	{
		return mData.getClipTop();
	}

	DipT getBaseWidth() const final
	{
		return mData.getBaseWidth();
	}

	DipT getBaseHeight() const final
	{
		return mData.getBaseHeight();
	}

	void delegateMouse(DipT X, DipT Y) final
	{
		mData.delegateMouse(X, Y);
	}
};

template<typename T>
class WidgetAdaptorT
:
	public T
{
protected:
	using T::getWidget;

public:
	// Widget
	template<typename ... ArgsT>
	void init(ArgsT && ... Args)
	{
		getWidget().init(std::forward<ArgsT>(Args) ...);
	}

	void moveX(DipT X)
	{
		getWidget().moveX(X);
	}

	void moveY(DipT Y)
	{
		getWidget().moveY(Y);
	}

	void resizeWidth(DipT X)
	{
		getWidget().resizeWidth(X);
	}

	void resizeHeight(DipT Y)
	{
		getWidget().resizeHeight(Y);
	}

	void setClipLeft(DipT X)
	{
		getWidget().setClipLeft(X);
	}

	void setClipRight(DipT X)
	{
		getWidget().setClipRight(X);
	}

	void setClipBottom(DipT Y)
	{
		getWidget().setClipBottom(Y);
	}

	void setClipTop(DipT Y)
	{
		getWidget().setClipTop(Y);
	}

	DipT getLeft() const
	{
		return getWidget().getLeft();
	}

	DipT getBottom() const
	{
		return getWidget().getBottom();
	}

	DipT getRight() const
	{
		return getWidget().getRight();
	}

	DipT getTop() const
	{
		return getWidget().getTop();
	}

	DipT getClipLeft() const
	{
		return getWidget().getClipLeft();
	}

	DipT getClipBottom() const
	{
		return getWidget().getClipBottom();
	}

	DipT getClipRight() const
	{
		return getWidget().getClipRight();
	}

	DipT getClipTop() const
	{
		return getWidget().getClipTop();
	}

	DipT getBaseWidth() const
	{
		return getWidget().getBaseWidth();
	}

	DipT getBaseHeight() const
	{
		return getWidget().getBaseHeight();
	}

	void delegateMouse(DipT X, DipT Y)
	{
		getWidget().delegateMouse(X, Y);
	}
};

}
}
