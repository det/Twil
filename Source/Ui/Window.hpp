#pragma once

#include "Gl/Context.hpp"
#include "Math/Matrix3.hpp"
#include "Ui/Event.hpp"
#include "Theme/Manager.hpp"
#include "Ui/WindowControl.hpp"
#include "Ui/Application.hpp"

#include <iostream>
#include <stdexcept>
#include <GL3/gl3.h>

namespace Twil {
namespace Ui {

template <typename T>
class Window
{
	private:
	Platform::Window mWindow;
	Theme::Manager mThemeManager;
	Ui::WindowControl mControl;
	T mChild;
	int mWidth = 0;
	int mHeight = 0;
	bool mIsFullscreen = false;

	public:
	Ui::Event<> Deleted;

	Window(Platform::Application &);

	T & getChild();

	void handleMouseEnter(int, int);
	void handleMouseLeave(int, int);
	void handleMouseMotion(int, int);
	void handleButtonPressed(int, int, unsigned);
	void handleButtonReleased(int, int, unsigned);
	void handleKeyPressed(Platform::Key);
	void handleKeyReleased(Platform::Key);
	void handleResized(unsigned short, unsigned short);
	void handleExposed();
	void handleDeleted();

	void draw();
	void show();
	void hide();
	void update();
	void toggleFullscreen();
	void resize(unsigned short, unsigned short);
	void fitChild(unsigned short, unsigned short);
};

template <typename T>
Window<T>::Window(Platform::Application & Application) :
	mWindow{Application},
	mChild{mThemeManager, mControl}
{
}

template <typename T>
void Window<T>::handleMouseEnter(int X, int Y)
{
	mChild.handleMouseEnter(X, Y);
}

template <typename T>
void Window<T>::handleMouseLeave(int X, int Y)
{
	mChild.handleMouseLeave(X, Y);
}

template <typename T>
void Window<T>::handleMouseMotion(int X, int Y)
{
	mChild.handleMouseMotion(X, Y);
}

template <typename T>
void Window<T>::handleButtonPressed(int X, int Y, unsigned Button)
{
	mChild.handleButtonPressed(X, Y, Button);
}

template <typename T>
void Window<T>::handleButtonReleased(int X, int Y, unsigned Button)
{
	mChild.handleButtonReleased(X, Y, Button);
}

template <typename T>
void Window<T>::handleKeyPressed(Platform::Key Key)
{
	mChild.handleKeyPressed(Key);
}

template <typename T>
void Window<T>::handleKeyReleased(Platform::Key Key)
{
	mChild.handleKeyReleased(Key);
}

template <typename T>
void Window<T>::handleResized(unsigned short Width, unsigned short Height)
{
	mWidth = Width;
	mHeight = Height;
	mChild.handleResized(mWidth, mHeight);
}

template <typename T>
void Window<T>::handleExposed()
{
	mControl.setNeedsRedraw(true);
}

template <typename T>
void Window<T>::handleDeleted()
{
	Deleted();
}

template <typename T>
void Window<T>::update()
{
	if (!mControl.getNeedsRedraw()) return;
	draw();
	mControl.setNeedsRedraw(false);
}

template <typename T>
void Window<T>::draw()
{
	if (mWidth == 0 || mHeight == 0) return;

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
void Window<T>::fitChild(unsigned short PadWidth, unsigned short PadHeight)
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
