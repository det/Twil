#pragma once

#include "Gl/Context.hpp"
#include "Theme/Button.hpp"
#include "Ui/Event.hpp"
#include "Ui/Window.hpp"

#include <stdexcept>

namespace Twil {
namespace Ui {

class WindowControl;

template<typename T>
class Button :
	public Widget
{
	private:
	Ui::WindowControl & mControl;
	Theme::Button mThemeButton;
	T mChild;
	bool mIsPressed;
	bool mHasMouse;

	public:
	Event<> Clicked;

	Button(Theme::Manager &, Ui::WindowControl &);
	~Button();

	T & getChild();

	virtual void handleMouseEnter(int, int);
	virtual void handleMouseLeave(int, int);
	virtual void handleButtonPressed(int, int, unsigned);
	virtual void handleButtonReleased(int, int, unsigned);
	virtual void handleMouseMotion(int, int) {}
	virtual void handleKeyPressed(Platform::Key) {}
	virtual void handleKeyReleased(Platform::Key) {}

	virtual void handleResized(unsigned short, unsigned short);
	virtual void handleMoved(short, short);
	virtual void draw();
};

template<typename T>
Button<T>::Button(Theme::Manager & Theme, Ui::WindowControl & Control) :
	mControl{Control},
	mThemeButton{Theme},
	mChild{Theme, mControl},
	mIsPressed{false},
	mHasMouse{false}
{
	mChild.handleMoved(2, 2);
}

template<typename T>
Button<T>::~Button()
{
}

template<typename T>
void Button<T>::handleMouseEnter(int, int)
{
	mHasMouse = true;
	if (mIsPressed) {
		mThemeButton.setIsDown(true);
		mControl.setNeedsRedraw(true);
	}
}

template<typename T>
void Button<T>::handleMouseLeave(int, int)
{
	mHasMouse = false;
	if (mIsPressed) {
		mThemeButton.setIsDown(false);
		mControl.setNeedsRedraw(true);
	}
}

template<typename T>
void Button<T>::handleButtonPressed(int, int, unsigned Button)
{
	if (Button == 1) {
		mIsPressed = true;
		mThemeButton.setIsDown(true);
		mControl.setNeedsRedraw(true);
	}
}

template<typename T>
void Button<T>::handleButtonReleased(int, int, unsigned Button)
{
	if (Button == 1) {
		if (mHasMouse) {
			mThemeButton.setIsDown(false);
			Clicked();
		}
		mIsPressed = false;
		mControl.setNeedsRedraw(true);
	}
}

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
void Button<T>::draw()
{
	mThemeButton.render();
	mChild.draw();
}

template<typename T>
T & Button<T>::getChild()
{
	return mChild;
}

}
}
