#pragma once

#include "WidgetFwd.hpp"

#include "ContainerFwd.hpp"
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
	virtual void moveX(float Delta) = 0;

	/// \brief Move the bottom and top position and clipping bounds.
	virtual void moveY(float Delta) = 0;

	/// \brief Move the right position and clipping bound.
	virtual void resizeWidth(float Delta) = 0;

	/// \brief Move the top position and clipping bound.
	virtual void resizeHeight(float Delta) = 0;

	/// \brief Set the left clipping bound.
	virtual void setClipLeft(float Absolute) = 0;

	/// \brief Set the right clipping bound.
	virtual void setClipRight(float Absolute) = 0;

	/// \brief Set the bottom clipping bound.
	virtual void setClipBottom(float Absolute) = 0;

	/// \brief Set the top clipping bound.
	virtual void setClipTop(float Absolute) = 0;

	/// \returns The left position bound.
	virtual float getLeft() const = 0;

	/// \returns The bottom position bound.
	virtual float getBottom() const = 0;

	/// \returns The right position bound.
	virtual float getRight() const = 0;

	/// \returns The top position bound.
	virtual float getTop() const = 0;

	/// \returns The left clip line.
	virtual float getClipLeft() const = 0;

	/// \returns The right clip line.
	virtual float getClipRight() const = 0;

	/// \returns The bottom clip line.
	virtual float getClipBottom() const = 0;

	/// \returns The top clip line.
	virtual float getClipTop() const = 0;

	/// \returns The base width.
	virtual float getBaseWidth() const = 0;

	/// \returns The base height.
	virtual float getBaseHeight() const = 0;

	/// \brief Take control of the mouse or pass it to someone else.
	virtual void delegateMouse(float X, float Y) = 0;
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

	void moveX(float Delta) final
	{
		mData.moveX(Delta);
	}

	void moveY(float Delta) final
	{
		mData.moveY(Delta);
	}

	void resizeWidth(float Delta) final
	{
		mData.resizeWidth(Delta);
	}

	void resizeHeight(float Delta) final
	{
		mData.resizeHeight(Delta);
	}

	void setClipLeft(float Absolute) final
	{
		mData.setClipLeft(Absolute);
	}

	void setClipRight(float Absolute) final
	{
		mData.setClipRight(Absolute);
	}

	void setClipBottom(float Absolute) final
	{
		mData.setClipBottom(Absolute);
	}

	void setClipTop(float Absolute) final
	{
		mData.setClipTop(Absolute);
	}

	float getLeft() const final
	{
		return mData.getLeft();
	}

	float getBottom() const final
	{
		return mData.getBottom();
	}

	float getRight() const final
	{
		return mData.getRight();
	}

	float getTop() const final
	{
		return mData.getTop();
	}

	float getClipLeft() const final
	{
		return mData.getClipLeft();
	}

	float getClipRight() const final
	{
		return mData.getClipRight();
	}

	float getClipBottom() const final
	{
		return mData.getClipBottom();
	}

	float getClipTop() const final
	{
		return mData.getClipTop();
	}

	float getBaseWidth() const final
	{
		return mData.getBaseWidth();
	}

	float getBaseHeight() const final
	{
		return mData.getBaseHeight();
	}

	void delegateMouse(float X, float Y) final
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

	void moveX(float X)
	{
		getWidget().moveX(X);
	}

	void moveY(float Y)
	{
		getWidget().moveY(Y);
	}

	void resizeWidth(float X)
	{
		getWidget().resizeWidth(X);
	}

	void resizeHeight(float Y)
	{
		getWidget().resizeHeight(Y);
	}

	void setClipLeft(float X)
	{
		getWidget().setClipLeft(X);
	}

	void setClipRight(float X)
	{
		getWidget().setClipRight(X);
	}

	void setClipBottom(float Y)
	{
		getWidget().setClipBottom(Y);
	}

	void setClipTop(float Y)
	{
		getWidget().setClipTop(Y);
	}

	float getLeft() const
	{
		return getWidget().getLeft();
	}

	float getBottom() const
	{
		return getWidget().getBottom();
	}

	float getRight() const
	{
		return getWidget().getRight();
	}

	float getTop() const
	{
		return getWidget().getTop();
	}

	float getClipLeft() const
	{
		return getWidget().getClipLeft();
	}

	float getClipBottom() const
	{
		return getWidget().getClipBottom();
	}

	float getClipRight() const
	{
		return getWidget().getClipRight();
	}

	float getClipTop() const
	{
		return getWidget().getClipTop();
	}

	float getBaseWidth() const
	{
		return getWidget().getBaseWidth();
	}

	float getBaseHeight() const
	{
		return getWidget().getBaseHeight();
	}

	void delegateMouse(float X, float Y)
	{
		getWidget().delegateMouse(X, Y);
	}
};

}
}
