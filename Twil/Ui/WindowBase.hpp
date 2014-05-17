#pragma once

#include "WindowBaseFwd.hpp"

#include "KeyboardHandlerFwd.hpp"
#include "MouseHandlerFwd.hpp"
#include "WindowHandlerFwd.hpp"
#include "Platform/KeyFwd.hpp"
#include "Platform/Window.hpp"
#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

class WindowConverterT
{
private:	
	std::int64_t mDipToPixelFactorX;
	std::int64_t mDipToPixelFactorY;
	std::int64_t mPixelToDipFactorX;
	std::int64_t mPixelToDipFactorY;
	std::int64_t mHalfPixelX;
	std::int64_t mHalfPixelY;

public:
	WindowConverterT(Platform::ApplicationT & Application);

	PixelT convertDipToPixelX(DipT X);
	PixelT convertDipToPixelY(DipT Y);
	DipT convertPixelToDipX(PixelT X);
	DipT convertPixelToDipY(PixelT X);
	PixelT scaleX(PixelT X);
	PixelT scaleY(PixelT Y);
};

class WindowBaseT
:
	public WindowConverterT,
	public Platform::WindowT
{
	WindowBaseT(WindowBaseT const &) = delete;
	WindowBaseT & operator =(WindowBaseT const &) = delete;

private:
	PixelT mPixelWidth;
	PixelT mPixelHeight;
	Ui::KeyboardHandlerT * mKeyboardHandler;
	Ui::MouseHandlerT * mMouseHandler;
	Ui::WindowHandlerT * mWindowHandler;
	Theme::ManagerT mTheme;

public:
	WindowBaseT(Platform::ApplicationT & Application, DipT Width, DipT Height);

	PixelT getPixelWidth();
	PixelT getPixelHeight();

	Ui::KeyboardHandlerT & getKeyboardHandler();
	Ui::MouseHandlerT & getMouseHandler();
	Ui::WindowHandlerT & getWindowHandler();

	void setKeyboardHandler(Ui::KeyboardHandlerT & KeyboardHandler);
	void setMouseHandler(Ui::MouseHandlerT & MouseHandler);
	void setWindowHandler(Ui::WindowHandlerT & WindowHandler);

	Theme::ManagerT & getThemeManager();

	void handleKeyPress(Platform::KeyT Key);
	void handleKeyRelease(Platform::KeyT Key);

	void handleMouseMotion(PixelT X, PixelT Y);
	void handleButtonPress(PixelT X, PixelT Y, std::uint8_t Index);
	void handleButtonRelease(PixelT X, PixelT Y, std::uint8_t Index);
	void handleMouseLeaveWindow(PixelT X, PixelT Y);
	void handleMouseEnterWindow(PixelT X, PixelT Y);

	void handleWindowExposed();
	void handleWindowDeleted();
	void handleWindowResize(PixelT Width, PixelT Height);
	void handleWindowUpdate();

	void resize(DipT Width, DipT Height);
};


}
}
