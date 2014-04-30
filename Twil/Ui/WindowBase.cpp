#include "WindowBase.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowHandler.hpp"
#include "Platform/Application.hpp"
#include "Theme/Settings.hpp"

namespace Twil {
namespace Ui {

WindowConverterT::WindowConverterT(float DpiX, float DpiY)
:
	mDipToPixelFactorX{DpiX / 96.0f},
	mDipToPixelFactorY{DpiY / 96.0f},
	mPixelToDipFactorX{96.0f / DpiX},
	mPixelToDipFactorY{96.0f / DpiY}
{}

std::int16_t WindowConverterT::convertDipToPixelX(float X)
{
	return std::lround(X * mDipToPixelFactorX);
}

std::int16_t WindowConverterT::convertDipToPixelY(float Y)
{
	return std::lround(Y * mDipToPixelFactorY);
}

float WindowConverterT::convertPixelToDipX(std::int16_t X)
{
	return X * mPixelToDipFactorX;
}

float WindowConverterT::convertPixelToDipY(std::int16_t Y)
{
	return Y * mPixelToDipFactorY;
}

WindowBaseT::WindowBaseT(Platform::ApplicationT & Application, float Width, float Height)
:
	WindowConverterT{Application.getDpiX(), Application.getDpiY()},
	Platform::WindowT{
		*this,
		Application,
		convertDipToPixelX(Width),
		convertDipToPixelY(Height)},
	mTheme{*this}
{}

std::int16_t WindowBaseT::getPixelWidth()
{
	return mPixelWidth;
}

std::int16_t WindowBaseT::getPixelHeight()
{
	return mPixelHeight;
}

Ui::KeyboardHandlerT & WindowBaseT::getKeyboardHandler()
{
	return *mKeyboardHandler;
}

Ui::MouseHandlerT & WindowBaseT::getMouseHandler()
{
	return *mMouseHandler;
}

Ui::WindowHandlerT & WindowBaseT::getWindowHandler()
{
	return *mWindowHandler;
}

Theme::ManagerT & WindowBaseT::getThemeManager()
{
	return mTheme;
}

void WindowBaseT::setKeyboardHandler(Ui::KeyboardHandlerT & KeyboardHandler)
{
	mKeyboardHandler = &KeyboardHandler;
}

void WindowBaseT::setMouseHandler(Ui::MouseHandlerT & MouseHandler)
{
	mMouseHandler = &MouseHandler;
}

void WindowBaseT::setWindowHandler(Ui::WindowHandlerT & WindowHandler)
{
	mWindowHandler = &WindowHandler;
}

void WindowBaseT::handleKeyPress(Platform::KeyT Key)
{
	getKeyboardHandler().handleKeyPress(Key);
}

void WindowBaseT::handleKeyRelease(Platform::KeyT Key)
{
	getKeyboardHandler().handleKeyRelease(Key);
}

void WindowBaseT::handleMouseMotion(std::int16_t X, std::int16_t Y)
{
	getMouseHandler().handleMouseMotion(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y));
}

void WindowBaseT::handleButtonPress(std::int16_t X, std::int16_t Y, std::uint8_t Index)
{
	getMouseHandler().handleButtonPress(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y),
		Index);
}

void WindowBaseT::handleButtonRelease(std::int16_t X, std::int16_t Y, std::uint8_t Index)
{
	getMouseHandler().handleButtonRelease(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y),
		Index);
}

void WindowBaseT::handleMouseLeaveWindow(std::int16_t X, std::int16_t Y)
{
	getMouseHandler().handleMouseLeaveWindow(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y));
}

void WindowBaseT::handleMouseEnterWindow(std::int16_t X, std::int16_t Y)
{
	getMouseHandler().handleMouseEnterWindow(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y));
}

void WindowBaseT::handleWindowExposed()
{
	getWindowHandler().handleWindowExposed();
}

void WindowBaseT::handleWindowDeleted()
{
	getWindowHandler().handleWindowDeleted();
}

void WindowBaseT::handleWindowResize(std::int16_t Width, std::int16_t Height)
{
	if (mPixelWidth != Width)
	{
		mPixelWidth = Width;
		getWindowHandler().handleWindowResizeWidth(convertPixelToDipX(Width));
	}

	if (mPixelHeight != Height)
	{
		mPixelHeight = Height;
		getWindowHandler().handleWindowResizeHeight(convertPixelToDipY(Height));
	}
}

void WindowBaseT::handleWindowUpdate()
{
	auto b = getThemeManager().update(mPixelWidth, mPixelHeight);
	if (b) swapBuffers();
}

void WindowBaseT::resize(float Width, float Height)
{
	resizePixels(
		convertDipToPixelX(Width),
		convertDipToPixelY(Height));
}

}
}
