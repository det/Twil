#pragma once

#include "Ui/Tuple.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"

#include <iostream>

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {

class WindowBase;

template<typename... Args>
class HorizontalBox :
	public Ui::Widget,
	public Ui::WidgetContainer
{
	private:
	Ui::WidgetContainer & mParent;
	Ui::Tuple<Args...> mChildren;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	static std::size_t const mSize = sizeof...(Args);

	public:
	HorizontalBox(Ui::WidgetContainer &, Theme::Manager &, Ui::WindowBase &);

	template<std::size_t I>
	typename Ui::TupleElement<I, Args...>::Type & getChild();

	// Drawable
	virtual void handleResized(unsigned short, unsigned short) override;
	virtual void handleMoved(signed short, signed short) override;
	virtual unsigned short getFitWidth() override;
	virtual unsigned short getFitHeight() override;
	virtual void draw() override;

	// Widget
	virtual void aquireMouse(signed short, signed short) override;

	// WidgetContainer
	virtual void releaseMouse(signed short, signed short) override;
};

template<typename... Args>
HorizontalBox<Args...>::HorizontalBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
	mParent{Parent},
	mChildren{*this, Theme, Base}
{}


template<typename... Args>
template<std::size_t I>
typename Ui::TupleElement<I, Args...>::Type & HorizontalBox<Args...>::getChild()
{
	return Ui::TupleElement<I, Args...>().get(mChildren);
}

// Drawable

struct ResizeFunctor
{
	unsigned short Width;
	unsigned short Height;

	template<typename T>
	void operator()(T & Child)
	{
		Child.handleResized(Width, Height);
	}
};

struct MoveFunctor
{
	signed short X;
	signed short Y;
	unsigned short BoxWidth;

	template<typename T>
	void operator()(T & Child)
	{
		Child.handleMoved(X, Y);
		X += BoxWidth;
	}
};

template<typename... Args>
void HorizontalBox<Args...>::handleResized(unsigned short Width, unsigned short Height)
{
	mWidth = Width;
	mHeight = Height;

	unsigned short BoxWidth = mWidth / mSize;
	mChildren.iterate(ResizeFunctor{BoxWidth, Height});
	mChildren.iterate(MoveFunctor{mX, mY, BoxWidth});
}

template<typename... Args>
void HorizontalBox<Args...>::handleMoved(short X, short Y)
{
	mX = X;
	mY = Y;
	unsigned short BoxWidth = mWidth / mSize;
	mChildren.iterate(MoveFunctor{mX, mY, BoxWidth});
}

struct MaxWidthFunctor
{
	unsigned short & MaxWidth;

	template<typename T>
	void operator()(T & Child)
	{
		auto Width = Child.getFitWidth();
		MaxWidth = std::max(MaxWidth, Width);
	}
};

template<typename... Args>
unsigned short HorizontalBox<Args...>::getFitWidth()
{
	unsigned short MaxWidth = 0;
	mChildren.iterate(MaxWidthFunctor{MaxWidth});
	return MaxWidth * mSize;
}

struct MaxHeightFunctor
{
	unsigned short & MaxHeight;

	template<typename T>
	void operator()(T & Child)
	{
		auto Height = Child.getFitHeight();
		MaxHeight = std::max(MaxHeight, Height);
	}
};

template<typename... Args>
unsigned short HorizontalBox<Args...>::getFitHeight()
{
	unsigned short MaxHeight = 0;
	mChildren.iterate(MaxHeightFunctor{MaxHeight});
	return MaxHeight;
}

struct DrawFunctor
{
	template<typename T>
	void operator()(T & Child)
	{
		Child.draw();
	}
};

template<typename... Args>
void HorizontalBox<Args...>::draw()
{
	mChildren.iterate(DrawFunctor{});
}

// Widget

struct AquireMouseFunctor
{
	signed short X;
	signed short Y;
	unsigned short BoxWidth;
	signed short Min;
	signed short Max;

	template<typename T>
	void operator()(T & Child)
	{
		if (X > Min && X < Max) Child.aquireMouse(X, Y);
		Min = Max;
		Max += BoxWidth;
	}
};

template<typename... Args>
void HorizontalBox<Args...>::aquireMouse(signed short X, signed short Y)
{
	unsigned short BoxWidth = mWidth / mSize;
	signed short Min = 0;
	signed short Max = BoxWidth;
	mChildren.iterate(AquireMouseFunctor{X, Y, BoxWidth, Min, Max});
}

// WidgetContainer

template<typename... Args>
void HorizontalBox<Args...>::releaseMouse(signed short X, signed short Y)
{
	auto MinX = mX;
	auto MaxX = mX + mWidth;
	auto MinY = mY;
	auto MaxY = mY + mHeight;

	if (X >= MinX && X <= MaxX && Y >= MinY && Y <= MaxY) aquireMouse(X, Y);
	else mParent.releaseMouse(X, Y);
}

}
}
