#pragma once

#include <cstdint>
#include <utility>

namespace Twil {
namespace Ui {

class ContainerT;
class WindowBaseT;

class WidgetT
{
public:
	virtual ~WidgetT() = default;

	/// \brief Initialize the widget
	virtual void init(ContainerT & Parent, WindowBaseT & Window) = 0;

	/// \brief Move the left and right position and clipping bounds.
	virtual void moveX(std::int16_t Delta) = 0;

	/// \brief Move the bottom and top position and clipping bounds.
	virtual void moveY(std::int16_t Delta) = 0;

	/// \brief Move the right position and clipping bound.
	virtual void resizeWidth(std::int16_t Delta) = 0;

	/// \brief Move the top position and clipping bound.
	virtual void resizeHeight(std::int16_t Delta) = 0;

	/// \brief Set the left clipping bound.
	virtual void setClipLeft(std::int16_t Absolute) = 0;

	/// \brief Set the right clipping bound.
	virtual void setClipRight(std::int16_t Absolute) = 0;

	/// \brief Set the bottom clipping bound.
	virtual void setClipBottom(std::int16_t Absolute) = 0;

	/// \brief Set the top clipping bound.
	virtual void setClipTop(std::int16_t Absolute) = 0;

	/// \returns The left position bound.
	virtual std::int16_t getLeft() const = 0;

	/// \returns The bottom position bound.
	virtual std::int16_t getBottom() const = 0;

	/// \returns The right position bound.
	virtual std::int16_t getRight() const = 0;

	/// \returns The top position bound.
	virtual std::int16_t getTop() const = 0;

	/// \returns The left clip line.
	virtual std::int16_t getClipLeft() const = 0;

	/// \returns The right clip line.
	virtual std::int16_t getClipRight() const = 0;

	/// \returns The bottom clip line.
	virtual std::int16_t getClipBottom() const = 0;

	/// \returns The top clip line.
	virtual std::int16_t getClipTop() const = 0;

	/// \returns The base width.
	virtual std::int16_t getBaseWidth() const = 0;

	/// \returns The base height.
	virtual std::int16_t getBaseHeight() const = 0;

	/// \brief Take control of the mouse or pass it to someone else.
	virtual void delegateMouse(std::int16_t X, std::int16_t Y) = 0;
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

	void moveX(std::int16_t Delta) final
	{
		mData.moveX(Delta);
	}

	void moveY(std::int16_t Delta) final
	{
		mData.moveY(Delta);
	}

	void resizeWidth(std::int16_t Delta) final
	{
		mData.resizeWidth(Delta);
	}

	void resizeHeight(std::int16_t Delta) final
	{
		mData.resizeHeight(Delta);
	}

	void setClipLeft(std::int16_t Absolute) final
	{
		mData.setClipLeft(Absolute);
	}

	void setClipRight(std::int16_t Absolute) final
	{
		mData.setClipRight(Absolute);
	}

	void setClipBottom(std::int16_t Absolute) final
	{
		mData.setClipBottom(Absolute);
	}

	void setClipTop(std::int16_t Absolute) final
	{
		mData.setClipTop(Absolute);
	}

	std::int16_t getLeft() const final
	{
		return mData.getLeft();
	}

	std::int16_t getBottom() const final
	{
		return mData.getBottom();
	}

	std::int16_t getRight() const final
	{
		return mData.getRight();
	}

	std::int16_t getTop() const final
	{
		return mData.getTop();
	}

	std::int16_t getClipLeft() const final
	{
		return mData.getClipLeft();
	}

	std::int16_t getClipRight() const final
	{
		return mData.getClipRight();
	}

	std::int16_t getClipBottom() const final
	{
		return mData.getClipBottom();
	}

	std::int16_t getClipTop() const final
	{
		return mData.getClipTop();
	}

	std::int16_t getBaseWidth() const final
	{
		return mData.getBaseWidth();
	}

	std::int16_t getBaseHeight() const final
	{
		return mData.getBaseHeight();
	}

	void delegateMouse(std::int16_t X, std::int16_t Y) final
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

	void moveX(std::int16_t X)
	{
		getWidget().moveX(X);
	}

	void moveY(std::int16_t Y)
	{
		getWidget().moveY(Y);
	}

	void resizeWidth(std::int16_t X)
	{
		getWidget().resizeWidth(X);
	}

	void resizeHeight(std::int16_t Y)
	{
		getWidget().resizeHeight(Y);
	}

	void setClipLeft(std::int16_t X)
	{
		getWidget().setClipLeft(X);
	}

	void setClipRight(std::int16_t X)
	{
		getWidget().setClipRight(X);
	}

	void setClipBottom(std::int16_t Y)
	{
		getWidget().setClipBottom(Y);
	}

	void setClipTop(std::int16_t Y)
	{
		getWidget().setClipTop(Y);
	}

	std::int16_t getLeft() const
	{
		return getWidget().getLeft();
	}

	std::int16_t getBottom() const
	{
		return getWidget().getBottom();
	}

	std::int16_t getRight() const
	{
		return getWidget().getRight();
	}

	std::int16_t getTop() const
	{
		return getWidget().getTop();
	}

	std::int16_t getClipLeft() const
	{
		return getWidget().getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return getWidget().getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return getWidget().getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return getWidget().getClipTop();
	}

	std::int16_t getBaseWidth() const
	{
		return getWidget().getBaseWidth();
	}

	std::int16_t getBaseHeight() const
	{
		return getWidget().getBaseHeight();
	}

	void delegateMouse(std::int16_t X, std::int16_t Y)
	{
		getWidget().delegateMouse(X, Y);
	}
};

}
}
