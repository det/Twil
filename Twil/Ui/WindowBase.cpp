#include "WindowBase.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowHandler.hpp"
#include "Platform/Application.hpp"
#include "Theme/Settings.hpp"

#include <iostream>

namespace Twil {
namespace Ui {

WindowConverterT::WindowConverterT(Platform::ApplicationT & Application)
:
	mDipToPixelFactorX{17045651456 * Application.getPixelWidth() / (15 * Application.getMillimeterWidth())},
	mDipToPixelFactorY{17045651456 * Application.getPixelHeight() / (15 * Application.getMillimeterHeight())},
	mPixelToDipFactorX{2061584302080 * Application.getMillimeterWidth() / (127 * Application.getPixelWidth())},
	mPixelToDipFactorY{2061584302080 * Application.getMillimeterHeight() / (127 * Application.getPixelHeight())},
	mHalfPixelX{mPixelToDipFactorX / 131072},
	mHalfPixelY{mPixelToDipFactorY / 131072}
{}

std::int16_t WindowConverterT::convertDipToPixelX(std::int32_t X)
{
	if (X > 0) X += mHalfPixelX;
	else X -= mHalfPixelX;
	return X * mDipToPixelFactorX / 281474976710656;
}

std::int16_t WindowConverterT::convertDipToPixelY(std::int32_t Y)
{
	if (Y > 0) Y += mHalfPixelY;
	else Y -= mHalfPixelY;
	return Y * mDipToPixelFactorY / 281474976710656;
}

std::int32_t WindowConverterT::convertPixelToDipX(std::int16_t X)
{
	return X * mPixelToDipFactorX / 65536;
}

std::int32_t WindowConverterT::convertPixelToDipY(std::int16_t Y)
{
	return Y * mPixelToDipFactorY / 65536;
}

std::int16_t WindowConverterT::scaleX(std::int16_t X)
{
	return convertDipToPixelX(X * 65536);
}

std::int16_t WindowConverterT::scaleY(std::int16_t Y)
{
	return convertDipToPixelY(Y * 65536);
}

WindowBaseT::WindowBaseT(Platform::ApplicationT & Application, std::int32_t Width, std::int32_t Height)
:
	WindowConverterT{Application},
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

void WindowBaseT::resize(std::int32_t Width, std::int32_t Height)
{
	resizePixels(
		convertDipToPixelX(Width),
		convertDipToPixelY(Height));
}

}
}
