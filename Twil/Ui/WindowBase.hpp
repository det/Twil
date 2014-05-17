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

	std::int16_t convertDipToPixelX(DipT X);
	std::int16_t convertDipToPixelY(DipT Y);
	DipT convertPixelToDipX(std::int16_t X);
	DipT convertPixelToDipY(std::int16_t X);
	std::int16_t scaleX(std::int16_t X);
	std::int16_t scaleY(std::int16_t Y);
};

class WindowBaseT
:
	public WindowConverterT,
	public Platform::WindowT
{
	WindowBaseT(WindowBaseT const &) = delete;
	WindowBaseT & operator =(WindowBaseT const &) = delete;

private:
	std::int16_t mPixelWidth;
	std::int16_t mPixelHeight;
	Ui::KeyboardHandlerT * mKeyboardHandler;
	Ui::MouseHandlerT * mMouseHandler;
	Ui::WindowHandlerT * mWindowHandler;
	Theme::ManagerT mTheme;

public:
	WindowBaseT(Platform::ApplicationT & Application, DipT Width, DipT Height);

	std::int16_t getPixelWidth();
	std::int16_t getPixelHeight();

	Ui::KeyboardHandlerT & getKeyboardHandler();
	Ui::MouseHandlerT & getMouseHandler();
	Ui::WindowHandlerT & getWindowHandler();

	void setKeyboardHandler(Ui::KeyboardHandlerT & KeyboardHandler);
	void setMouseHandler(Ui::MouseHandlerT & MouseHandler);
	void setWindowHandler(Ui::WindowHandlerT & WindowHandler);

	Theme::ManagerT & getThemeManager();

	void handleKeyPress(Platform::KeyT Key);
	void handleKeyRelease(Platform::KeyT Key);

	void handleMouseMotion(std::int16_t X, std::int16_t Y);
	void handleButtonPress(std::int16_t X, std::int16_t Y, std::uint8_t Index);
	void handleButtonRelease(std::int16_t X, std::int16_t Y, std::uint8_t Index);
	void handleMouseLeaveWindow(std::int16_t X, std::int16_t Y);
	void handleMouseEnterWindow(std::int16_t X, std::int16_t Y);

	void handleWindowExposed();
	void handleWindowDeleted();
	void handleWindowResize(std::int16_t Width, std::int16_t Height);
	void handleWindowUpdate();

	void resize(DipT Width, DipT Height);
};


}
}
