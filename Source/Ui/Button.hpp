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
	//Button
	Event<> Clicked;

	Button(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent{Parent},
		mBase{Base},
		mThemeButton{Theme},
		mChild{*this, Theme, mBase},
		mIsPressed{false},
		mHasMouse{false}
	{
		mChild.handleMoved(2, 2);
	}

	T & getChild()
	{
		return mChild;
	}

	// Widget
	virtual void aquireMouse(signed short, signed short) override
	{
		mBase.setMouseHandler(*this);
		mHasMouse = true;
	}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mThemeButton.resize(Width, Height);
		auto ChildWidth = mThemeButton.getChildWidth();
		auto ChildHeight = mThemeButton.getChildHeight();
		mChild.handleResized(ChildWidth, ChildHeight);
	}

	virtual void handleMoved(signed short X, signed short Y) override
	{
		mThemeButton.move(X, Y);
		auto ChildX = mThemeButton.getChildX();
		auto ChildY = mThemeButton.getChildY();
		mChild.handleMoved(ChildX, ChildY);
	}

	virtual unsigned short getFitWidth() override
	{
		auto Width = mChild.getFitWidth();
		return mThemeButton.getFitWidth(Width);
	}

	virtual unsigned short getFitHeight() override
	{
		auto Height = mChild.getFitHeight();
		return mThemeButton.getFitHeight(Height);
	}

	virtual void draw() override
	{
		mThemeButton.render();
		mChild.draw();
	}

	unsigned short getX() override
	{
		return mThemeButton.getX();
	}

	unsigned short getY() override
	{
		return mThemeButton.getY();
	}

	unsigned short getWidth() override
	{
		return mThemeButton.getWidth();
	}

	unsigned short getHeight() override
	{
		return mThemeButton.getHeight();
	}

	// MouseHandler
	virtual void handleButtonPress(signed short, signed short, unsigned char Button) override
	{
		if (Button == 1) {
			mIsPressed = true;
			mThemeButton.setIsDown(true);
			mBase.markNeedsRedraw();
		}
	}

	virtual void handleButtonRelease(signed short X, signed short Y, unsigned char Button) override
	{

		if (Button == 1) {
			if (!mIsPressed) return;
			if (mHasMouse) {
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

	virtual void handleMouseMotion(signed short X, signed short Y) override
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
};

}
}
