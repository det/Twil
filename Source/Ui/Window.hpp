#pragma once

#include "Gl/Context.hpp"
#include "Math/Matrix3.hpp"
#include "Theme/Manager.hpp"
#include "Ui/Application.hpp"
#include "Ui/Event.hpp"
#include "Ui/KeyboardHandler.hpp"
#include "Ui/MouseHandler.hpp"
#include "Ui/WidgetContainer.hpp"
#include "Ui/WindowBase.hpp"


#include <iostream>
#include <stdexcept>
#include <GL3/gl3.h>

namespace Twil {
namespace Ui {

template <typename T>
class Window :
	public Ui::KeyboardHandler,
	public Ui::MouseHandler,
	public Ui::WidgetContainer,
	public Ui::WindowBase
{
	private:
	Platform::Window mWindow;
	Theme::Manager mThemeManager;
	T mChild;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;
	bool mIsFullscreen = false;

	public:
	Ui::Event<> Deleted;

	Window(Platform::Application &);

	// Mousehandler
	virtual void handleMouseEnterWindow(signed short, signed short) override;
	virtual void handleMouseMotion(signed short, signed short) override;

	// WidgetContainer
	virtual void releaseMouse(signed short, signed short) override;

	// Window
	void handleExposed();
	void handleDeleted();
	void handleResize(unsigned short, unsigned short);
	void draw();
	void show();
	void hide();
	void update();
	void toggleFullscreen();
	void resize(unsigned short, unsigned short);
	void fitChild(signed short, signed short);
	unsigned short getWidth() { return mWidth; }
	unsigned short getHeight() { return mHeight; }

	T & getChild();
};

template <typename T>
Window<T>::Window(Platform::Application & Application) :
	Ui::WindowBase{this, this},
	mWindow{Application},
	mChild{*this, mThemeManager, *this}
{}

// MouseHandler

template <typename T>
void Window<T>::handleMouseMotion(signed short X, signed short Y)
{
	if (X >= 0 && X <= mWidth && Y >= 0 && Y <= mHeight) mChild.aquireMouse(X, Y);
}

template <typename T>
void Window<T>::handleMouseEnterWindow(signed short X, signed short Y)
{
	mChild.aquireMouse(X, Y);
}

// WidgetContainer

template <typename T>
void Window<T>::releaseMouse(signed short, signed short)
{
	setMouseHandler(*this);
}

// Window

template <typename T>
void Window<T>::update()
{
	if (mNeedsResize) {
		mChild.handleResized(mWidth, mHeight);
		mNeedsResize = false;
	}
	if (mNeedsRedraw) {
		draw();
		mNeedsRedraw = false;
	}
}

template <typename T>
void Window<T>::handleExposed()
{
	mNeedsRedraw = true;
}

template <typename T>
void Window<T>::handleDeleted()
{
	Deleted();
}

template <typename T>
void Window<T>::handleResize(unsigned short Width, unsigned short Height)
{
	mWidth = Width;
	mHeight = Height;
	mNeedsResize = true;
}

template <typename T>
void Window<T>::draw()
{
	mThemeManager.beginRender(mWidth, mHeight);
	mThemeManager.renderWindow();
	mChild.draw();
	mThemeManager.finishRender();
	mWindow.swapBuffers();
}

template <typename T>
void Window<T>::toggleFullscreen()
{
	mIsFullscreen = !mIsFullscreen;
	mWindow.setFullscreen(mIsFullscreen);
}

template <typename T>
void Window<T>::fitChild(signed short PadWidth, signed short PadHeight)
{
	auto Width = mChild.getFitWidth();
	auto Height = mChild.getFitHeight();
	mWindow.resize(Width + PadWidth, Height + PadHeight);
}

template <typename T>
void Window<T>::show()
{
	mWindow.show();
}

template <typename T>
void Window<T>::hide()
{
	mWindow.hide();
}

template <typename T>
void Window<T>::resize(unsigned short Width, unsigned short Height)
{
	mWindow.resize(Width, Height);
}

template <typename T>
T & Window<T>::getChild()
{
	return mChild;
}

}
}
