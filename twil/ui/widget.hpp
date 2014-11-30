#pragma once

#include "widget.hxx"

#include "container.hxx"
#include "unit.hxx"
#include "window_base.hxx"

#include <cstdint>
#include <utility>

namespace twil {
namespace ui {

class Widget
{
public:
	virtual ~Widget() = default;

	/// \brief Initialize the widget
	virtual void Init(Container & parent, WindowBase & window) = 0;

	/// \brief Move the left and right position and clipping bounds.
	virtual void MoveX(Dip delta) = 0;

	/// \brief Move the bottom and top position and clipping bounds.
	virtual void MoveY(Dip delta) = 0;

	/// \brief Move the right position and clipping bound.
	virtual void ResizeWidth(Dip delta) = 0;

	/// \brief Move the top position and clipping bound.
	virtual void ResizeHeight(Dip delta) = 0;

	/// \brief Set the left clipping bound.
	virtual void SetClipLeft(Dip absolute) = 0;

	/// \brief Set the right clipping bound.
	virtual void SetClipRight(Dip absolute) = 0;

	/// \brief Set the bottom clipping bound.
	virtual void SetClipBottom(Dip absolute) = 0;

	/// \brief Set the top clipping bound.
	virtual void SetClipTop(Dip absolute) = 0;

	/// \returns The left position bound.
	virtual Dip GetLeft() const = 0;

	/// \returns The bottom position bound.
	virtual Dip GetBottom() const = 0;

	/// \returns The right position bound.
	virtual Dip GetRight() const = 0;

	/// \returns The top position bound.
	virtual Dip GetTop() const = 0;

	/// \returns The left clip line.
	virtual Dip GetClipLeft() const = 0;

	/// \returns The right clip line.
	virtual Dip GetClipRight() const = 0;

	/// \returns The bottom clip line.
	virtual Dip GetClipBottom() const = 0;

	/// \returns The top clip line.
	virtual Dip GetClipTop() const = 0;

	/// \returns The base width.
	virtual Dip GetBaseWidth() const = 0;

	/// \returns The base height.
	virtual Dip GetBaseHeight() const = 0;

	/// \brief Take control of the mouse or pass it to someone else.
	virtual void DelegateMouse(Dip x, Dip y) = 0;
};

template<typename T>
class WidgetModel
:
	public Widget
{
private:
	T data_;

public:
	virtual void Init(Container & parent, WindowBase & window) final
	{
		data_.Init(parent, window);
	}

	void MoveX(Dip delta) final
	{
		data_.MoveX(delta);
	}

	void MoveY(Dip delta) final
	{
		data_.MoveY(delta);
	}

	void ResizeWidth(Dip delta) final
	{
		data_.ResizeWidth(delta);
	}

	void ResizeHeight(Dip delta) final
	{
		data_.ResizeHeight(delta);
	}

	void SetClipLeft(Dip absolute) final
	{
		data_.SetClipLeft(absolute);
	}

	void SetClipRight(Dip absolute) final
	{
		data_.SetClipRight(absolute);
	}

	void SetClipBottom(Dip absolute) final
	{
		data_.SetClipBottom(absolute);
	}

	void SetClipTop(Dip absolute) final
	{
		data_.SetClipTop(absolute);
	}

	Dip GetLeft() const final
	{
		return data_.GetLeft();
	}

	Dip GetBottom() const final
	{
		return data_.GetBottom();
	}

	Dip GetRight() const final
	{
		return data_.GetRight();
	}

	Dip GetTop() const final
	{
		return data_.GetTop();
	}

	Dip GetClipLeft() const final
	{
		return data_.GetClipLeft();
	}

	Dip GetClipRight() const final
	{
		return data_.GetClipRight();
	}

	Dip GetClipBottom() const final
	{
		return data_.GetClipBottom();
	}

	Dip GetClipTop() const final
	{
		return data_.GetClipTop();
	}

	Dip GetBaseWidth() const final
	{
		return data_.GetBaseWidth();
	}

	Dip GetBaseHeight() const final
	{
		return data_.GetBaseHeight();
	}

	void DelegateMouse(Dip x, Dip y) final
	{
		data_.DelegateMouse(x, y);
	}
};

template<typename T>
class WidgetAdaptor
:
	public T
{
protected:
	using T::GetWidget;

public:
	// Widget
	template<typename ... Args>
	void Init(Args && ... args)
	{
		GetWidget().Init(std::forward<Args>(args) ...);
	}

	void MoveX(Dip x)
	{
		GetWidget().MoveX(x);
	}

	void MoveY(Dip y)
	{
		GetWidget().MoveY(y);
	}

	void ResizeWidth(Dip x)
	{
		GetWidget().ResizeWidth(x);
	}

	void ResizeHeight(Dip y)
	{
		GetWidget().ResizeHeight(y);
	}

	void SetClipLeft(Dip x)
	{
		GetWidget().SetClipLeft(x);
	}

	void SetClipRight(Dip x)
	{
		GetWidget().SetClipRight(x);
	}

	void SetClipBottom(Dip y)
	{
		GetWidget().SetClipBottom(y);
	}

	void SetClipTop(Dip y)
	{
		GetWidget().SetClipTop(y);
	}

	Dip GetLeft() const
	{
		return GetWidget().GetLeft();
	}

	Dip GetBottom() const
	{
		return GetWidget().GetBottom();
	}

	Dip GetRight() const
	{
		return GetWidget().GetRight();
	}

	Dip GetTop() const
	{
		return GetWidget().GetTop();
	}

	Dip GetClipLeft() const
	{
		return GetWidget().GetClipLeft();
	}

	Dip GetClipBottom() const
	{
		return GetWidget().GetClipBottom();
	}

	Dip GetClipRight() const
	{
		return GetWidget().GetClipRight();
	}

	Dip GetClipTop() const
	{
		return GetWidget().GetClipTop();
	}

	Dip GetBaseWidth() const
	{
		return GetWidget().GetBaseWidth();
	}

	Dip GetBaseHeight() const
	{
		return GetWidget().GetBaseHeight();
	}

	void DelegateMouse(Dip x, Dip y)
	{
		GetWidget().DelegateMouse(x, y);
	}
};

}
}
