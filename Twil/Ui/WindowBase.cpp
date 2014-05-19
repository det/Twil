#include "WindowBase.hpp"

#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowHandler.hpp"
#include "Platform/Application.hpp"
#include "Theme/Settings.hpp"

#include <iostream>

namespace {

template<typename T, typename CountT>
constexpr auto shar(T Num, CountT Count)
{
	static_assert(-1 >> 1 == -1, "signed right shift is not arithmetic shift");
	return Num >> Count;
}

template<typename T, typename CountT>
constexpr auto shal(T Num, CountT Count)
{
	return Num * (1 << Count);
}

}

namespace Twil {
namespace Ui {

WindowConverterT::WindowConverterT(Platform::ApplicationT & Application)
:
	mDipToPixelFactorX{
		(Application.getPixelWidth() * 17045651456) /
		(Application.getMillimeterWidth() * 15)},
	mDipToPixelFactorY{
		(Application.getPixelHeight() * 17045651456) /
		(Application.getMillimeterHeight() * 15)},
	mPixelToDipFactorX{
		(Application.getMillimeterWidth() * 2061584302080) /
		(Application.getPixelWidth() * 127)},
	mPixelToDipFactorY{
		(Application.getMillimeterHeight() * 2061584302080) /
		(Application.getPixelHeight() * 127)}
{}

PixelT WindowConverterT::convertDipToPixelX(DipT X)
{
	return shar((X + shar(mPixelToDipFactorX, 17)) * mDipToPixelFactorX, 48);
}

PixelT WindowConverterT::convertDipToPixelY(DipT Y)
{
	return shar((Y + shar(mPixelToDipFactorY, 17)) * mDipToPixelFactorY, 48);
}

DipT WindowConverterT::convertPixelToDipX(PixelT X)
{
	return shar(X * mPixelToDipFactorX, 16);
}

DipT WindowConverterT::convertPixelToDipY(PixelT Y)
{
	return shar(Y * mPixelToDipFactorY, 16);
}

PixelT WindowConverterT::scaleX(PixelT X)
{
	return convertDipToPixelX(shal(X, 16));
}

PixelT WindowConverterT::scaleY(PixelT Y)
{
	return convertDipToPixelY(shal(Y, 16));
}

WindowBaseT::WindowBaseT(Platform::ApplicationT & Application, DipT Width, DipT Height)
:
	WindowConverterT{Application},
	Platform::WindowT{
		*this,
		Application,
		convertDipToPixelX(Width),
		convertDipToPixelY(Height)},
	mTheme{*this}
{}

PixelT WindowBaseT::getPixelWidth()
{
	return mPixelWidth;
}

PixelT WindowBaseT::getPixelHeight()
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

void WindowBaseT::handleMouseMotion(PixelT X, PixelT Y)
{
	getMouseHandler().handleMouseMotion(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y));
}

void WindowBaseT::handleButtonPress(PixelT X, PixelT Y, std::uint8_t Index)
{
	getMouseHandler().handleButtonPress(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y),
		Index);
}

void WindowBaseT::handleButtonRelease(PixelT X, PixelT Y, std::uint8_t Index)
{
	getMouseHandler().handleButtonRelease(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y),
		Index);
}

void WindowBaseT::handleMouseLeaveWindow(PixelT X, PixelT Y)
{
	getMouseHandler().handleMouseLeaveWindow(
		convertPixelToDipX(X),
		convertPixelToDipY(mPixelHeight - Y));
}

void WindowBaseT::handleMouseEnterWindow(PixelT X, PixelT Y)
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

void WindowBaseT::handleWindowResize(PixelT Width, PixelT Height)
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

void WindowBaseT::resize(DipT Width, DipT Height)
{
	resizePixels(
		convertDipToPixelX(Width),
		convertDipToPixelY(Height));
}

}
}
