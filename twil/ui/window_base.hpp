#pragma once

#include "window_base.hxx"

#include "keyboard_handler.hxx"
#include "mouse_handler.hxx"
#include "window_handler.hxx"
#include "platform/key.hxx"
#include "platform/window.hpp"
#include "theme/manager.hpp"

namespace twil {
namespace ui {

class WindowConverter
{
private:	
	Scale dip_to_pixel_factor_x_;
	Scale dip_to_pixel_factor_y_;
	Scale pixel_to_dip_factor_x_;
	Scale pixel_to_dip_factor_y_;

public:
	WindowConverter(platform::Application & application);

	Pixel ConvertDipToPixelX(Dip x);
	Pixel ConvertDipToPixelY(Dip y);
	Dip ConvertPixelToDipX(Pixel x);
	Dip ConvertPixelToDipY(Pixel y);
	Pixel ScaleX(Pixel x);
	Pixel ScaleY(Pixel y);
};

class WindowBase
:
	public WindowConverter,
	public platform::Window
{
	WindowBase(WindowBase const &) = delete;
	WindowBase & operator =(WindowBase const &) = delete;

private:
	Pixel pixel_width_;
	Pixel pixel_height_;
	ui::KeyboardHandler * keyboard_handler_;
	ui::MouseHandler * mouse_handler_;
	ui::WindowHandler * window_handler_;
	theme::Manager theme_;

public:
	WindowBase(platform::Application & application, Dip width, Dip height);

	Pixel GetPixelWidth();
	Pixel GetPixelHeight();

	ui::KeyboardHandler & GetKeyboardHandler();
	ui::MouseHandler & GetMouseHandler();
	ui::WindowHandler & GetWindowHandler();

	void SetKeyboardHandler(ui::KeyboardHandler & keyboard_handler);
	void SetMouseHandler(ui::MouseHandler & mouse_handler);
	void SetWindowHandler(ui::WindowHandler & window_handler);

	theme::Manager & GetThemeManager();

	void HandleKeyPress(platform::Key key);
	void HandleKeyRelease(platform::Key key);

	void HandleMouseMotion(Pixel x, Pixel y);
	void HandleButtonPress(Pixel x, Pixel y, std::uint8_t index);
	void HandleButtonRelease(Pixel x, Pixel y, std::uint8_t index);
	void HandleMouseLeaveWindow(Pixel x, Pixel y);
	void HandleMouseEnterWindow(Pixel x, Pixel y);

	void HandleWindowExposed();
	void HandleWindowDeleted();
	void HandleWindowResize(Pixel width, Pixel height);
	void HandleWindowUpdate();

	void Resize(Dip width, Dip height);
};


}
}
