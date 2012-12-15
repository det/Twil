#pragma once

#include "Gl/Context.hpp"
#include "Theme/Button.hpp"
#include "Ui/DrawableContainer.hpp"
#include "Ui/Event.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"
#include "Ui/Window.hpp"

#include <stdexcept>

namespace Twil {
namespace Ui {

class WindowBase;

template<typename T>
class Button :
	public Ui::DrawableContainer,
	public Ui::MouseHandler,
	public Ui::Widget
{
	private:
	Ui::WidgetContainer & mParent;
	Ui::WindowBase & mBase;
	Theme::Button mThemeButton;
	T mChild;
	bool mIsPressed;
	bool mHasMouse;

	public:
	Event<> Clicked;

	Button(Ui::WidgetContainer &, Theme::Manager &, Ui::WindowBase &);
	~Button();

	T & getChild();

	// Widget
	virtual void aquireMouse(signed short, signed short) override;

	// Drawable
	virtual void handleResized(unsigned short, unsigned short) override;
	virtual void handleMoved(short, short) override;
	virtual unsigned short getFitWidth() override;
	virtual unsigned short getFitHeight() override;
	virtual void draw() override;
	unsigned short getX() override { return mThemeButton.getX(); }
	unsigned short getY() override { return mThemeButton.getY(); }
	unsigned short getWidth() override { return mThemeButton.getWidth(); }
	unsigned short getHeight() override { return mThemeButton.getHeight(); }

	// MouseHandler
	virtual void handleButtonPress(signed short, signed short, unsigned char) override;
	virtual void handleButtonRelease(signed short, signed short, unsigned char) override;
	virtual void handleMouseMotion(signed short, signed short) override;
};

template<typename T>
Button<T>::Button(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
	mParent{Parent},
	mBase{Base},
	mThemeButton{Theme},
	mChild{*this, Theme, mBase},
	mIsPressed{false},
	mHasMouse{false}
{
	mChild.handleMoved(2, 2);
}

template<typename T>
Button<T>::~Button()
{
}

// Widget

template<typename T>
void Button<T>::aquireMouse(signed short, signed short)
{
	mBase.setMouseHandler(*this);
	mHasMouse = true;
}


// Drawable

template<typename T>
void Button<T>::handleResized(unsigned short Width, unsigned short Height)
{
	mThemeButton.resize(Width, Height);
	auto ChildWidth = mThemeButton.getChildWidth();
	auto ChildHeight = mThemeButton.getChildHeight();
	mChild.handleResized(ChildWidth, ChildHeight);
}

template<typename T>
void Button<T>::handleMoved(short Width, short Height)
{
	mThemeButton.move(Width, Height);
	auto ChildX = mThemeButton.getChildX();
	auto ChildY = mThemeButton.getChildY();
	mChild.handleMoved(ChildX, ChildY);
}

template<typename T>
unsigned short Button<T>::getFitWidth()
{
	auto Width = mChild.getFitWidth();
	return mThemeButton.getFitWidth(Width);
}

template<typename T>
unsigned short Button<T>::getFitHeight()
{
	auto Height = mChild.getFitHeight();
	return mThemeButton.getFitHeight(Height);
}

template<typename T>
void Button<T>::draw()
{
	mThemeButton.render();
	mChild.draw();
}


// MouseHandler

template<typename T>
void Button<T>::handleButtonPress(signed short, signed short, unsigned char Button)
{
	if (Button == 1) {
		if (mHasMouse && !mIsPressed) {
			mIsPressed = true;
			mThemeButton.setIsDown(true);
			mBase.markNeedsRedraw();
		}
	}
}

template<typename T>
void Button<T>::handleButtonRelease(signed short X, signed short Y, unsigned char Button)
{
	if (Button == 1) {
		if (mHasMouse && mIsPressed) {
			mIsPressed = false;
			mThemeButton.setIsDown(false);
			mBase.markNeedsRedraw();
			Clicked();
		}
		else {
			mIsPressed = false;
			mParent.releaseMouse(X, Y);
		}
	}
}

template<typename T>
void Button<T>::handleMouseMotion(signed short X, signed short Y)
{
	auto MinX = mThemeButton.getX();
	auto MaxX = MinX + mThemeButton.getWidth();
	auto MinY = mThemeButton.getY();
	auto MaxY = MinY + mThemeButton.getHeight();
	bool HasMouse = X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY;

	if (mHasMouse && !HasMouse) {
		mHasMouse = false;
		if (mIsPressed) {
			mThemeButton.setIsDown(false);
			mBase.markNeedsRedraw();
		}
		else mParent.releaseMouse(X, Y);
	}
	else if (!mHasMouse && HasMouse) {
		mHasMouse = true;
		if (mIsPressed) {
			mThemeButton.setIsDown(true);
			mBase.markNeedsRedraw();
		}
	}
}

// Button

template<typename T>
T & Button<T>::getChild()
{
	return mChild;
}

}
}
