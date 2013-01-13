#pragma once

#include "Theme/Manager.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"
#include "Ui/WindowBase.hpp"

namespace Twil {
namespace Ui {

template<typename A, typename B>
class SplitBoxBase :
	public Ui::Widget<true, true>,
	public Ui::WidgetContainer<true, true>
{
	protected:
	Ui::WidgetContainer<true, true> & mParent;
	A mA;
	B mB;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	// SplitBox
	SplitBoxBase(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
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
	virtual void setX(signed short X) override
	{
		signed short DeltaX = X - mX;
		mX = X;
		signed short ChildAX = mA.getX();
		signed short ChildBX = mB.getX();
		mA.setX(ChildAX + DeltaX);
		mB.setX(ChildBX + DeltaX);
	}

	virtual void setY(signed short Y) override
	{
		signed short DeltaY = Y - mY;
		mY = Y;
		signed short ChildAY = mA.getY();
		signed short ChildBY = mB.getY();
		mA.setY(ChildAY + DeltaY);
		mB.setY(ChildBY + DeltaY);
	}

	virtual void setClipX(signed short, signed short) override
	{}

	virtual void setClipY(signed short, signed short) override
	{}

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
	SplitBoxHorizontal(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
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
	using Ui::SplitBoxBase<A, B>::mA;
	using Ui::SplitBoxBase<A, B>::mB;

	public:
	SplitBoxVertical(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
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
	SplitBox(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxVertical<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void setWidth(unsigned short Width) override
	{
		mWidth = Width;
		mA.setWidth(mWidth);
		mB.setWidth(mWidth);
	}

	virtual void setHeight(unsigned short Height) override
	{
		mHeight = Height;

		unsigned short FitHeightB = mB.getFitHeight();
		if (mHeight >= FitHeightB) {
			unsigned short ExtraSpace = mHeight - FitHeightB;
			mA.setHeight(ExtraSpace);
			mB.setHeight(FitHeightB);
			mA.setY(mY);
			mB.setY(mY + ExtraSpace);
		}
		else {
			mA.setHeight(0);
			mB.setHeight(mHeight);
			mA.setY(mY);
			mB.setY(mY + 0);
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
	SplitBox(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxVertical<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void setWidth(unsigned short Width) override
	{
		mWidth = Width;
		mA.setWidth(mWidth);
		mB.setWidth(mWidth);
	}

	virtual void setHeight(unsigned short Height) override
	{
		mHeight = Height;

		unsigned short FitHeightA = mA.getFitHeight();
		if (mHeight >= FitHeightA) {
			unsigned short ExtraSpace = mHeight - FitHeightA;
			mA.setHeight(FitHeightA);
			mB.setHeight(ExtraSpace);
			mB.setY(mY + FitHeightA);
		}
		else {
			mA.setHeight(mHeight);
			mB.setHeight(0);
			mB.setY(mY + mHeight);
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
	SplitBox(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxHorizontal<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void setWidth(unsigned short Width) override
	{
		mWidth = Width;

		unsigned short FitWidthB = mB.getFitWidth();
		if (mWidth >= FitWidthB) {
			unsigned short ExtraSpace = mWidth - FitWidthB;
			mA.setWidth(ExtraSpace);
			mB.setWidth(FitWidthB);
			mB.setX(mX + ExtraSpace);
		}
		else {
			mA.setWidth(0);
			mB.setWidth(mWidth);
			mB.setX(mX + 0);
		}
	}

	virtual void setHeight(unsigned short Height) override
	{
		mHeight = Height;
		mA.setHeight(mHeight);
		mB.setHeight(mHeight);
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
	SplitBox(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		Ui::SplitBoxHorizontal<A, B>{Parent, Theme, Base}
	{}

	// Drawable
	virtual void setWidth(unsigned short Width) override
	{
		mWidth = Width;

		unsigned short FitWidthA = mA.getFitWidth();
		if (mWidth >= FitWidthA) {
			unsigned short ExtraSpace = mWidth - FitWidthA;
			mA.setWidth(FitWidthA);
			mB.setWidth(ExtraSpace);
			mB.setX(mX + FitWidthA);
		}
		else {
			mA.setWidth(mWidth);
			mB.setWidth(0);
			mB.setX(mX + mWidth);
		}
	}

	virtual void setHeight(unsigned short Height) override
	{
		mHeight = Height;
		mA.setHeight(mHeight);
		mB.setHeight(mHeight);
	}
};

}
}
