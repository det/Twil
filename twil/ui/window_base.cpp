#include "window_base.hpp"

#include "keyboard_handler.hpp"
#include "mouse_handler.hpp"
#include "window_handler.hpp"
#include "platform/application.hpp"
#include "theme/settings.hpp"

#include <iostream>

namespace {

template<typename T, typename Count>
constexpr auto Shar(T num, Count count)
{
	static_assert(-1 >> 1 == -1, "signed right shift is not arithmetic shift");
	return num >> count;
}

template<typename T, typename Count>
constexpr auto Shal(T num, Count count)
{
	return num * (1 << count);
}

}

namespace twil {
namespace ui {

WindowConverter::WindowConverter(platform::Application & application)
:
	dip_to_pixel_factor_x_{
		(application.GetPixelWidth() * 17045651456) /
		(application.GetMillimeterWidth() * 15)},
	dip_to_pixel_factor_y_{
		(application.GetPixelHeight() * 17045651456) /
		(application.GetMillimeterHeight() * 15)},
	pixel_to_dip_factor_x_{
		(application.GetMillimeterWidth() * 2061584302080) /
		(application.GetPixelWidth() * 127)},
	pixel_to_dip_factor_y_{
		(application.GetMillimeterHeight() * 2061584302080) /
		(application.GetPixelHeight() * 127)}
{}

Pixel WindowConverter::ConvertDipToPixelX(Dip x)
{
	return Shar((x + Shar(pixel_to_dip_factor_x_, 17)) * dip_to_pixel_factor_x_, 48);
}

Pixel WindowConverter::ConvertDipToPixelY(Dip y)
{
	return Shar((y + Shar(pixel_to_dip_factor_y_, 17)) * dip_to_pixel_factor_y_, 48);
}

Dip WindowConverter::ConvertPixelToDipX(Pixel x)
{
	return Shar(x * pixel_to_dip_factor_x_, 16);
}

Dip WindowConverter::ConvertPixelToDipY(Pixel y)
{
	return Shar(y * pixel_to_dip_factor_y_, 16);
}

Pixel WindowConverter::ScaleX(Pixel x)
{
	return ConvertDipToPixelX(Shal(x, 16));
}

Pixel WindowConverter::ScaleY(Pixel y)
{
	return ConvertDipToPixelY(Shal(y, 16));
}

WindowBase::WindowBase(platform::Application & application, Dip width, Dip height)
:
	WindowConverter{application},
	platform::Window{
		*this,
		application,
		ConvertDipToPixelX(width),
		ConvertDipToPixelY(height)},
	theme_{*this}
{}

Pixel WindowBase::GetPixelWidth()
{
	return pixel_width_;
}

Pixel WindowBase::GetPixelHeight()
{
	return pixel_height_;
}

ui::KeyboardHandler & WindowBase::GetKeyboardHandler()
{
	return *keyboard_handler_;
}

ui::MouseHandler & WindowBase::GetMouseHandler()
{
	return *mouse_handler_;
}

ui::WindowHandler & WindowBase::GetWindowHandler()
{
	return *window_handler_;
}

theme::Manager & WindowBase::GetThemeManager()
{
	return theme_;
}

void WindowBase::SetKeyboardHandler(ui::KeyboardHandler & keyboard_handler)
{
	keyboard_handler_ = &keyboard_handler;
}

void WindowBase::SetMouseHandler(ui::MouseHandler & mouse_handler)
{
	mouse_handler_ = &mouse_handler;
}

void WindowBase::SetWindowHandler(ui::WindowHandler & window_handler)
{
	window_handler_ = &window_handler;
}

void WindowBase::HandleKeyPress(platform::Key key)
{
	GetKeyboardHandler().HandleKeyPress(key);
}

void WindowBase::HandleKeyRelease(platform::Key key)
{
	GetKeyboardHandler().HandleKeyRelease(key);
}

void WindowBase::HandleMouseMotion(Pixel x, Pixel y)
{
	GetMouseHandler().HandleMouseMotion(
		ConvertPixelToDipX(x),
		ConvertPixelToDipY(pixel_height_ - y));
}

void WindowBase::HandleButtonPress(Pixel x, Pixel y, std::uint8_t index)
{
	GetMouseHandler().HandleButtonPress(
		ConvertPixelToDipX(x),
		ConvertPixelToDipY(pixel_height_ - y),
		index);
}

void WindowBase::HandleButtonRelease(Pixel x, Pixel y, std::uint8_t index)
{
	GetMouseHandler().HandleButtonRelease(
		ConvertPixelToDipX(x),
		ConvertPixelToDipY(pixel_height_ - y),
		index);
}

void WindowBase::HandleMouseLeaveWindow(Pixel x, Pixel y)
{
	GetMouseHandler().HandleMouseLeaveWindow(
		ConvertPixelToDipX(x),
		ConvertPixelToDipY(pixel_height_ - y));
}

void WindowBase::HandleMouseEnterWindow(Pixel x, Pixel y)
{
	GetMouseHandler().HandleMouseEnterWindow(
		ConvertPixelToDipX(x),
		ConvertPixelToDipY(pixel_height_ - y));
}

void WindowBase::HandleWindowExposed()
{
	GetWindowHandler().HandleWindowExposed();
}

void WindowBase::HandleWindowDeleted()
{
	GetWindowHandler().HandleWindowDeleted();
}

void WindowBase::HandleWindowResize(Pixel width, Pixel height)
{
	if (pixel_width_ != width)
	{
		pixel_width_ = width;
		GetWindowHandler().HandleWindowResizeWidth(ConvertPixelToDipX(width));
	}

	if (pixel_height_ != height)
	{
		pixel_height_ = height;
		GetWindowHandler().HandleWindowResizeHeight(ConvertPixelToDipY(height));
	}
}

void WindowBase::HandleWindowUpdate()
{
	auto b = GetThemeManager().Update(pixel_width_, pixel_height_);
	if (b) SwapBuffers();
}

void WindowBase::Resize(Dip width, Dip height)
{
	ResizePixels(
		ConvertDipToPixelX(width),
		ConvertDipToPixelY(height));
}

}
}
