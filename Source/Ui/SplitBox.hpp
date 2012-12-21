#pragma once

#include "Theme/Manager.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"
#include "Ui/WindowBase.hpp"

namespace Twil {
namespace Ui {

template<typename A, typename B>
class SplitBoxBase :
	public Ui::Widget,
	public Ui::WidgetContainer
{
	protected:
	Ui::WidgetContainer & mParent;
	A mA;
	B mB;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	// SplitBox
	SplitBoxBase(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
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
	virtual void handleMoved(signed short X, signed short Y) override
	{
		signed short DeltaX = X - mX;
		signed short DeltaY = Y - mY;
		mX = X;
		mY = Y;
		mA.handleMoved(mA.getX() + DeltaX, mA.getY() + DeltaY);
		mB.handleMoved(mB.getX() + DeltaX, mB.getY() + DeltaY);
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

template<typename A, typename B>
class SplitBoxHorizontal :
	public Ui::SplitBoxBase<A, B>
{
	protected:
	using Ui::SplitBoxBase<A, B>::mA;
	using Ui::SplitBoxBase<A, B>::mB;

	public:
	SplitBoxHorizontal(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxBase<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual unsigned short getFitWidth() override
	{
		unsigned short FitWidthA = mA.getFitWidth();
		unsigned short FitWidthB = mB.getFitWidth();
		return FitWidthA + FitWidthB;
	}

	virtual unsigned short getFitHeight() override
	{
		unsigned short FitHeightA = mA.getFitHeight();
		unsigned short FitHeightB = mB.getFitHeight();
		return std::max(FitHeightA, FitHeightB);
	}

	// Widget
	virtual void aquireMouse(signed short X, signed short Y) override
	{
		if (X < mB.getX()) mA.aquireMouse(X, Y);
		else mB.aquireMouse(X, Y);
	}
};

template<typename A, typename B>
class SplitBoxVertical :
	public Ui::SplitBoxBase<A, B>
{
	protected:
	// This is neccesary because of C++'s two phase compilation
	using Ui::SplitBoxBase<A, B>::mA;
	using Ui::SplitBoxBase<A, B>::mB;

	public:
	SplitBoxVertical(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxBase<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual unsigned short getFitWidth() override
	{
		unsigned short FitWidthA = mA.getFitWidth();
		unsigned short FitWidthB = mB.getFitWidth();
		return std::max(FitWidthA, FitWidthB);
	}

	virtual unsigned short getFitHeight() override
	{
		unsigned short FitHeightA = mA.getFitHeight();
		unsigned short FitHeightB = mB.getFitHeight();
		return FitHeightA + FitHeightB;
	}

	// Widget
	virtual void aquireMouse(signed short X, signed short Y) override
	{
		if (Y < mB.getY()) mA.aquireMouse(X, Y);
		else mB.aquireMouse(X, Y);
	}
};

template<bool IsHorizontal, bool IsFirstStatic, typename A, typename B>
class SplitBox;

template<typename A, typename B>
class SplitBox<false, false, A, B> :
	public Ui::SplitBoxVertical<A, B>
{
	protected:
	using Ui::SplitBoxVertical<A, B>::mA;
	using Ui::SplitBoxVertical<A, B>::mB;
	using Ui::SplitBoxVertical<A, B>::mWidth;
	using Ui::SplitBoxVertical<A, B>::mHeight;
	using Ui::SplitBoxVertical<A, B>::mX;
	using Ui::SplitBoxVertical<A, B>::mY;

	public:
	// SplitBox
	SplitBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxVertical<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;


		unsigned short FitHeightB = mB.getFitHeight();
		if (mHeight >= FitHeightB) {
			unsigned short ExtraSpace = mHeight - FitHeightB;
			mA.handleResized(mWidth, ExtraSpace);
			mB.handleResized(mWidth, FitHeightB);
			mA.handleMoved(mX, mY);
			mB.handleMoved(mX, mY + ExtraSpace);
		}
		else {
			mA.handleResized(mWidth, 0);
			mB.handleResized(mWidth, mHeight);
			mA.handleMoved(mX, mY);
			mB.handleMoved(mX, mY + 0);
		}
	}
};

template<typename A, typename B>
class SplitBox<false, true, A, B> :
	public Ui::SplitBoxVertical<A, B>
{
	protected:
	using Ui::SplitBoxVertical<A, B>::mA;
	using Ui::SplitBoxVertical<A, B>::mB;
	using Ui::SplitBoxVertical<A, B>::mWidth;
	using Ui::SplitBoxVertical<A, B>::mHeight;
	using Ui::SplitBoxVertical<A, B>::mX;
	using Ui::SplitBoxVertical<A, B>::mY;

	public:
	// SplitBox
	SplitBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxVertical<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;

		unsigned short FitHeightA = mA.getFitHeight();
		if (mHeight >= FitHeightA) {
			unsigned short ExtraSpace = mHeight - FitHeightA;
			mA.handleResized(mWidth, FitHeightA);
			mB.handleResized(mWidth, ExtraSpace);
			mB.handleMoved(mX, mY + FitHeightA);
		}
		else {
			mA.handleResized(mWidth, mHeight);
			mB.handleResized(mWidth, 0);
			mB.handleMoved(mX, mY + mHeight);
		}
	}
};

template<typename A, typename B>
class SplitBox<true, false, A, B> :
	public Ui::SplitBoxHorizontal<A, B>
{
	protected:
	using Ui::SplitBoxHorizontal<A, B>::mA;
	using Ui::SplitBoxHorizontal<A, B>::mB;
	using Ui::SplitBoxHorizontal<A, B>::mWidth;
	using Ui::SplitBoxHorizontal<A, B>::mHeight;
	using Ui::SplitBoxHorizontal<A, B>::mX;
	using Ui::SplitBoxHorizontal<A, B>::mY;

	public:
	// SplitBox
	SplitBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxHorizontal<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;

		unsigned short FitWidthB = mB.getFitWidth();
		if (mWidth >= FitWidthB) {
			unsigned short ExtraSpace = mWidth - FitWidthB;
			mA.handleResized(ExtraSpace, mHeight);
			mB.handleResized(FitWidthB, mHeight);
			mB.handleMoved(mX + ExtraSpace, mY);
		}
		else {
			mA.handleResized(0, mHeight);
			mB.handleResized(mWidth, mHeight);
			mB.handleMoved(mX + 0, mY);
		}
	}
};

template<typename A, typename B>
class SplitBox<true, true, A, B> :
	public Ui::SplitBoxHorizontal<A, B>
{
	protected:
	using Ui::SplitBoxHorizontal<A, B>::mA;
	using Ui::SplitBoxHorizontal<A, B>::mB;
	using Ui::SplitBoxHorizontal<A, B>::mWidth;
	using Ui::SplitBoxHorizontal<A, B>::mHeight;
	using Ui::SplitBoxHorizontal<A, B>::mX;
	using Ui::SplitBoxHorizontal<A, B>::mY;

	public:
	// SplitBox
	SplitBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxHorizontal<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;

		unsigned short FitWidthA = mA.getFitWidth();
		if (mWidth >= FitWidthA) {
			unsigned short ExtraSpace = mWidth - FitWidthA;
			mA.handleResized(FitWidthA, mHeight);
			mB.handleResized(ExtraSpace, mHeight);
			mB.handleMoved(mX + FitWidthA, mY);
		}
		else {
			mA.handleResized(mWidth, mHeight);
			mB.handleResized(0, mHeight);
			mB.handleMoved(mX + mWidth, mY);
		}
	}
};

}
}
