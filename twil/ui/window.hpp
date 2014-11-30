#pragma once

#include "window.hxx"

#include "application.hxx"
#include "container.hpp"
#include "keyboard_handler.hpp"
#include "mouse_handler.hpp"
#include "unit.hpp"
#include "window_base.hpp"
#include "window_handler.hpp"
#include "data/event.hpp"

namespace twil {
namespace ui {

using namespace udl;

/// \brief A resizable window that holds a single child widget.
/// \param T The type of the child widget.
template <typename T>
class Window
:
	public Container,
	public KeyboardHandler,
	public MouseHandler,
	public WindowHandler,
	public WindowBase
{
	Window(Window const &) = delete;
	Window & operator =(Window const &) = delete;

private:
	T child_;

	bool CheckChildContains(Dip x, Dip y)
	{
		return x >= 0 && x <= child_.GetRight() && y >= 0 && y <= child_.GetTop();
	}

public:
	// Window
	data::Event<> Deleted;

	Window(platform::Application & application)
	:
		WindowBase{application, 320_dip, 240_dip}
	{}

	void Init()
	{
		SetKeyboardHandler(*this);
		SetMouseHandler(*this);
		SetWindowHandler(*this);
		child_.Init(*this, *this);
	}

	/// \returns The width.
	Dip GetWidth() const
	{
		return child_.GetRight();
	}

	/// \returns The height.
	Dip GetHeight() const
	{
		return child_.GetTop();
	}

	/// \returns A reference to the child.
	T & GetChild()
	{
		return child_;
	}

	/// \returns A const reference to the child.
	T const & GetChild() const
	{
		return child_;
	}

	// WindowHandler
	void HandleWindowExposed() final
	{
		GetThemeManager().MarkNeedsRedraw();
	}

	void HandleWindowDeleted() final
	{
		Deleted();
	}

	void HandleWindowResizeWidth(Dip width) final
	{
		child_.ResizeWidth(width - GetWidth());
	}

	void HandleWindowResizeHeight(Dip height) final
	{
		child_.ResizeHeight(height - GetHeight());
	}

	// Container
	void ReleaseMouse(Dip, Dip) final
	{
		SetMouseHandler(*this);
	}

	void HandleChildBaseWidthChanged(void *) final
	{}

	void HandleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void HandleMouseMotion(Dip x, Dip y) final
	{
		if (CheckChildContains(x, y)) child_.DelegateMouse(x, y);
	}
};

}
}
