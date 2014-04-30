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
	float mDipToPixelFactorX;
	float mDipToPixelFactorY;
	float mPixelToDipFactorX;
	float mPixelToDipFactorY;

public:
	WindowConverterT(float DpiX, float DpiY);

	std::int16_t convertDipToPixelX(float X);
	std::int16_t convertDipToPixelY(float Y);
	float convertPixelToDipX(std::int16_t X);
	float convertPixelToDipY(std::int16_t X);
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
	WindowBaseT(Platform::ApplicationT & Application, float Width, float Height);

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

	void resize(float Width, float Height);
};


}
}
