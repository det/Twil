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
	public Ui::WidgetContainer<true, true>,
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
	// Window
	Ui::Event<> Deleted;

	Window(Platform::Application & Application) :
		Ui::WindowBase{this, this},
		mWindow{Application},
		mChild{*this, mThemeManager, *this}
	{}

	// Mousehandler
	virtual void handleMouseEnterWindow(signed short X, signed short Y) override
	{
		mChild.aquireMouse(X, Y);
	}

	virtual void handleMouseMotion(signed short X, signed short Y) override
	{
		if (X >= 0 && X <= mWidth && Y >= 0 && Y <= mHeight) mChild.aquireMouse(X, Y);
	}

	// WidgetContainer
	virtual void releaseMouse(signed short, signed short) override
	{
		setMouseHandler(*this);
	}

	// Window
	void handleExposed()
	{
		mNeedsRedraw = true;
	}

	void handleDeleted()
	{
		Deleted();
	}

	void handleResize(unsigned short Width, unsigned short Height)
	{
		mWidth = Width;
		mHeight = Height;
		mNeedsResize = true;
	}

	void draw()
	{
		mThemeManager.beginRender(mWidth, mHeight);
		mThemeManager.renderWindow();
		mChild.draw();
		mThemeManager.finishRender();
		mWindow.swapBuffers();
	}

	void show()
	{
		mWindow.show();
	}

	void hide()
	{
		mWindow.hide();
	}

	void update()
	{
		if (mNeedsResize) {
			mChild.setWidth(mWidth);
			mChild.setHeight(mHeight);
			mNeedsResize = false;
		}
		if (mNeedsRedraw) {
			draw();
			mNeedsRedraw = false;
		}
	}

	void toggleFullscreen()
	{
		mIsFullscreen = !mIsFullscreen;
		mWindow.setFullscreen(mIsFullscreen);
	}

	void resize(unsigned short Width, unsigned short Height)
	{
		mWindow.resize(Width, Height);
	}

	void fitChild(signed short PadWidth, signed short PadHeight)
	{
		auto Width = mChild.getFitWidth();
		auto Height = mChild.getFitHeight();
		mWindow.resize(Width + PadWidth, Height + PadHeight);
	}

	unsigned short getWidth()
	{
		return mWidth;
	}

	unsigned short getHeight()
	{
		return mHeight;
	}

	T & getChild()
	{
		return mChild;
	}
};

}
}
