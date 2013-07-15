#pragma once

#include <cstdint>

namespace Twil {
namespace Ui {

class ContainerT;
class WindowBaseT;

template<typename T>
class WidgetAdaptorT
:
	public T
{
	protected:
	using T::getWidget;

	public:
	// Widget
	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		getWidget().init(Parent, Window);
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
