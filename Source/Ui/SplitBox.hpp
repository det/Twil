#pragma once

#include "Theme/Manager.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"
#include "Ui/WindowBase.hpp"

namespace Twil {
namespace Ui {

template<bool IsHorizontal, bool DoesFirstShrink, bool DoesFirstGrow, typename A, typename B>
class SplitBox :
	public Ui::Widget,
	public Ui::WidgetContainer
{
	private:
	Ui::WidgetContainer & mParent;
	A mA;
	B mB;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	// SplitBox
	SplitBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent{Parent},
		mA{*this, Theme, Base},
		mB{*this, Theme, Base}
	{}

	A & getChild0()
	{
		return mA;
	}

	B & getChild1()
	{
		return mB;
	}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;

		if (IsHorizontal) {
			unsigned short WidthA = mA.getFitWidth();
			unsigned short WidthB = mB.getFitWidth();

			if (mWidth >= WidthA + WidthB) {
				if (DoesFirstGrow) WidthA = mWidth - WidthB;
				else WidthB = mWidth - WidthA;
			}
			else {
				if (DoesFirstShrink) {
					if (mWidth >= WidthB) WidthA = mWidth - WidthB;
					else {
						WidthA = 0;
						WidthB = mWidth;
					}
				}
				else {
					if (mWidth >= WidthA) WidthB = mWidth - WidthA;
					else {
						WidthA = mWidth;
						WidthB = 0;
					}
				}
			}

			mA.handleResized(WidthA, mHeight);
			mB.handleResized(WidthB, mHeight);
			mB.handleMoved(WidthA, mY);
		}
		else {
			unsigned short HeightA = mA.getFitHeight();
			unsigned short HeightB = mB.getFitHeight();

			if (mHeight >= HeightA + HeightB) {
				if (DoesFirstGrow) HeightA = mHeight - HeightB;
				else HeightB = mHeight - HeightA;
			}
			else {
				if (DoesFirstShrink) {
					if (mHeight >= HeightB) HeightA = mHeight - HeightB;
					else {
						HeightA = 0;
						HeightB = mHeight;
					}
				}
				else {
					if (mHeight >= HeightA) HeightB = mHeight - HeightA;
					else {
						HeightA = mHeight;
						HeightB = 0;
					}
				}
			}

			mA.handleResized(mWidth, HeightA);
			mB.handleResized(mWidth, HeightB);
			mB.handleMoved(mX, HeightA);
		}
	}

	virtual void handleMoved(signed short X, signed short Y) override
	{
		signed short DeltaX = X - mX;
		signed short DeltaY = Y - mY;
		mX = X;
		mY = Y;
		mA.handleMoved(mA.getX() + DeltaX, mA.getY() + DeltaY);
		mB.handleMoved(mB.getX() + DeltaX, mB.getY() + DeltaY);
	}

	virtual unsigned short getFitWidth() override
	{
		unsigned short FitWidthA = mA.getFitWidth();
		unsigned short FitWidthB = mB.getFitWidth();
		if (IsHorizontal) return FitWidthA + FitWidthB;
		else return std::max(FitWidthA, FitWidthB);
	}

	virtual unsigned short getFitHeight() override
	{
		unsigned short FitHeightA = mA.getFitHeight();
		unsigned short FitHeightB = mB.getFitHeight();
		if (IsHorizontal) return std::max(FitHeightA, FitHeightB);
		else return FitHeightA + FitHeightB;
	}

	virtual void draw() override
	{
		mA.draw();
		mB.draw();
	}

	virtual unsigned short getX() override
	{
		return mX;
	}

	virtual unsigned short getY() override {
		return mY;
	}

	virtual unsigned short getWidth() override
	{
		return mWidth;
	}

	virtual unsigned short getHeight() override
	{
		return mHeight;
	}

	// Widget
	virtual void aquireMouse(signed short X, signed short Y) override
	{
		if (IsHorizontal) {
			if (X < mB.getX()) mA.aquireMouse(X, Y);
			else mB.aquireMouse(X, Y);
		}
		else {
			if (Y < mB.getY()) mA.aquireMouse(X, Y);
			else mB.aquireMouse(X, Y);

		}
	}

	// WidgetContainer
	virtual void releaseMouse(signed short X, signed short Y) override
	{
		auto MinX = mX;
		auto MaxX = mX + mWidth;
		auto MinY = mY;
		auto MaxY = mY + mHeight;

		if (X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY) aquireMouse(X, Y);
		else mParent.releaseMouse(X, Y);
	}
};

}
}
