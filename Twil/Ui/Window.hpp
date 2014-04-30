#pragma once

#include "WindowFwd.hpp"

#include "ApplicationFwd.hpp"
#include "Container.hpp"
#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "WindowHandler.hpp"
#include "Data/Event.hpp"

namespace Twil {
namespace Ui {

/// \brief A resizable window that holds a single child widget.
/// \param T The type of the child widget.
template <typename T>
class WindowT
:
	public ContainerT,
	public KeyboardHandlerT,
	public MouseHandlerT,
	public WindowHandlerT,
	public WindowBaseT
{
	WindowT(WindowT const &) = delete;
	WindowT & operator =(WindowT const &) = delete;

private:
	T mChild;

	bool checkChildContains(float X, float Y)
	{
		return X >= 0 && X <= mChild.getRight() && Y >= 0 && Y <= mChild.getTop();
	}

public:
	// Window
	Data::EventT<> Deleted;

	WindowT(Platform::ApplicationT & Application)
	:
		WindowBaseT{Application, 320, 240}
	{}

	void init()
	{
		setKeyboardHandler(*this);
		setMouseHandler(*this);
		setWindowHandler(*this);
		mChild.init(*this, *this);
	}

	/// \returns The width.
	float getWidth() const
	{
		return mChild.getRight();
	}

	/// \returns The height.
	float getHeight() const
	{
		return mChild.getTop();
	}

	/// \returns A reference to the child.
	T & getChild()
	{
		return mChild;
	}

	/// \returns A const reference to the child.
	T const & getChild() const
	{
		return mChild;
	}

	// WindowHandler
	void handleWindowExposed() final
	{
		getThemeManager().markNeedsRedraw();
	}

	void handleWindowDeleted() final
	{
		Deleted();
	}

	void handleWindowResizeWidth(float Width) final
	{
		mChild.resizeWidth(Width - getWidth());
	}

	void handleWindowResizeHeight(float Height) final
	{
		mChild.resizeHeight(Height - getHeight());
	}

	// Container
	void releaseMouse(float, float) final
	{
		setMouseHandler(*this);
	}

	void handleChildBaseWidthChanged(void *) final
	{}

	void handleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void handleMouseMotion(float X, float Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
	}
};

}
}
