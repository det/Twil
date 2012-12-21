#pragma once

#include "Ui/MouseHandler.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"
#include "Ui/WindowBase.hpp"
#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

template<unsigned short SpaceX, unsigned short SpaceY, typename T>
class Border :
	public Ui::MouseHandler,
	public Ui::Widget,
	public Ui::WidgetContainer
{

	Ui::WidgetContainer & mParent;
	Ui::WindowBase & mBase;
	T mChild;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	// SplitBox
	Border(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent{Parent},
		mBase{Base},
		mChild{*this, Theme, Base}
	{}

	T & getChild()
	{
		return mChild;
	}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;
		unsigned short ChildWidth = 0;
		unsigned short ChildHeight = 0;
		if (mWidth >= SpaceX + SpaceX) ChildWidth = mWidth - SpaceX - SpaceX;
		if (mHeight >= SpaceY + SpaceY) ChildHeight = mHeight - SpaceY - SpaceY;
		mChild.handleResized(ChildWidth, ChildHeight);
		mChild.handleMoved(mX + SpaceX, mY + SpaceY);
	}

	virtual void handleMoved(signed short X, signed short Y) override
	{
		signed short DeltaX = X - mX;
		signed short DeltaY = Y - mY;
		mX = X;
		mY = Y;
		mChild.handleMoved(mChild.getX() + DeltaX, mChild.getY() + DeltaY);
	}

	virtual unsigned short getFitWidth() override
	{
		return mChild.getFitWidth() + SpaceX + SpaceX;
	}

	virtual unsigned short getFitHeight() override
	{
		return mChild.getFitHeight() + SpaceY + SpaceY;
	}

	virtual void draw() override
	{
		mChild.draw();
	}

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

	// MouseHandler
	virtual void handleMouseMotion(signed short X, signed short Y)
	{
		// Did the mouse enter the child
		auto MinX = mChild.getX();
		auto MaxX = MinX + mChild.getWidth();
		auto MinY = mChild.getY();
		auto MaxY = MinY + mChild.getHeight();
		if (X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY)  return mChild.aquireMouse(X, Y);

		// Did the mouse leave us
		MinX = mX;
		MaxX = MinX + mWidth;
		MinY = mY;
		MaxY = MinY + mHeight;
		if (X < MinX || X > MaxX || Y < MinY || Y > MaxY) return mParent.releaseMouse(X, Y);
	}

	// Widget
	virtual void aquireMouse(signed short X, signed short Y) override
	{
		auto MinX = mChild.getX();
		auto MaxX = MinX + mChild.getWidth();
		auto MinY = mChild.getY();
		auto MaxY = MinY + mChild.getHeight();

		if (X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY) mChild.aquireMouse(X, Y);
		else mBase.setMouseHandler(*this);
	}

	// WidgetContainer
	virtual void releaseMouse(signed short X, signed short Y) override
	{
		auto MinX = mX;
		auto MaxX = mX + mWidth;
		auto MinY = mY;
		auto MaxY = mY + mHeight;

		if (X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY) mBase.setMouseHandler(*this);
		else mParent.releaseMouse(X, Y);
	}
};

}
}
