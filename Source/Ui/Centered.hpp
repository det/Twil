#pragma once

#include "Ui/Drawable.hpp"
#include "Ui/DrawableContainer.hpp"

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {

class WindowBase;

template<typename MyChild>
class Centered :
	public Ui::Drawable<true, true>,
	public Ui::DrawableContainer<false, false>
{
	private:
	Ui::DrawableContainer<true, true> & mParent;
	Ui::WindowBase & mBase;
	MyChild mChild;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	// Cenetered
	Centered(Ui::DrawableContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mBase(Base), // Gcc bug prevents brace initialization syntax here
		mChild{*this, Theme, Base}
	{}

	MyChild & getChild()
	{
		return mChild;
	}

	// DrawableContainer
	virtual void handleChildWidthChanged() override
	{
		unsigned short ChildWidth = mChild.getWidth();
		signed short ChildX = mX + (mWidth - ChildWidth) / 2;
		mChild.setX(ChildX);
		signed short Min = mX - ChildX;
		signed short Max = (mX + mWidth) - ChildX;
		mChild.setClipX(Min, Max);
	}

	virtual void handleChildHeightChanged() override
	{
		unsigned short ChildHeight = mChild.getHeight();
		signed short ChildY = mY + (mHeight - ChildHeight) / 2;
		mChild.setY(ChildY);
		signed short Min = mY - ChildY;
		signed short Max = (mY + mHeight) - ChildY;
		mChild.setClipY(Min, Max);
	}

	// Drawable
	virtual void setX(signed short X) override
	{
		signed short DeltaX = X - mX;
		mX = X;
		signed short ChildX = mChild.getX();
		mChild.setX(ChildX + DeltaX);
	}

	virtual void setY(signed short Y) override
	{
		signed short DeltaY = Y - mY;
		mY = Y;
		signed short ChildY = mChild.getY();
		mChild.setY(ChildY + DeltaY);
	}

	virtual void setWidth(unsigned short Width) override
	{
		mWidth = Width;
		handleChildWidthChanged();
	}

	virtual void setHeight(unsigned short Height) override
	{
		mHeight = Height;
		handleChildHeightChanged();
	}

	virtual void setClipX(signed short, signed short) override
	{}

	virtual void setClipY(signed short, signed short) override
	{}

	virtual unsigned short getX() override
	{
		return mX;
	}

	virtual unsigned short getY() override
	{
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

	virtual unsigned short getFitWidth() override
	{
		return mChild.getFitWidth();
	}

	virtual unsigned short getFitHeight() override
	{
		return mChild.getFitHeight();
	}

	virtual void draw() override
	{
		mChild.draw();
	}
};

}
}
