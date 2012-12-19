#pragma once

#include "Ui/Tuple.hpp"
#include "Ui/Widget.hpp"
#include "Ui/WidgetContainer.hpp"

#include <algorithm>
#include <array>
#include <iostream>

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {

class WindowBase;

template<bool IsHorizontal, typename... Args>
class PartitionBox :
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
	// PartitionBox
	PartitionBox(Ui::WidgetContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent{Parent},
		mChildren{*this, Theme, Base}
	{}

	template<std::size_t I>
	typename Ui::TupleElement<I, Args...>::Type & getChild()
	{
		return Ui::TupleElement<I, Args...>().get(mChildren);
	}

	// Drawable
	struct ResizeHorizontalFunctor
	{
		signed short X;
		signed short Y;
		unsigned short BoxWidth;
		unsigned short Height;
		unsigned short Mod;

		template<typename T>
		void operator()(T & Child)
		{
			unsigned short Width = BoxWidth;
			if (Mod > 0) {
				++Width;
				--Mod;
			}
			Child.handleResized(Width, Height);
			Child.handleMoved(X, Y);
			X += Width;
		}
	};

	struct ResizeVerticalFunctor
	{
		signed short X;
		signed short Y;
		unsigned short Width;
		unsigned short BoxHeight;
		unsigned short Mod;

		template<typename T>
		void operator()(T & Child)
		{
			unsigned short Height = BoxHeight;
			if (Mod > 0) {
				++Height;
				--Mod;
			}
			Child.handleResized(Width, Height);
			Child.handleMoved(X, Y);
			Y += Height;
		}
	};

	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mWidth = Width;
		mHeight = Height;
		if (IsHorizontal) {
			unsigned short BoxWidth = Width / mSize;
			unsigned short Mod = Width % mSize;
			mChildren.iterate(ResizeHorizontalFunctor{mX, mY, BoxWidth, Height, Mod});
		}
		else {
			unsigned short BoxHeight = Height / mSize;
			unsigned short Mod = Height % mSize;
			mChildren.iterate(ResizeVerticalFunctor{mX, mY, Width, BoxHeight, Mod});
		}
	}

	struct MoveFunctor
	{
		signed short DeltaX;
		signed short DeltaY;

		template<typename T>
		void operator()(T & Child)
		{
			auto X = Child.getX();
			auto Y = Child.getY();
			Child.handleMoved(X + DeltaX, Y + DeltaY);
		}
	};

	virtual void handleMoved(signed short X, signed short Y) override
	{
		signed short DeltaX = X - mX;
		signed short DeltaY = Y - mY;
		mX = X;
		mY = Y;
		mChildren.iterate(MoveFunctor{DeltaX, DeltaY});
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

	virtual unsigned short getFitWidth() override
	{
		if (IsHorizontal) {
			unsigned short MaxWidth = 0;
			mChildren.iterate(MaxWidthFunctor{MaxWidth});
			return MaxWidth * mSize;
		}
		else {
			unsigned short MaxWidth = 0;
			mChildren.iterate(MaxWidthFunctor{MaxWidth});
			return MaxWidth;
		}
	}

	virtual unsigned short getFitHeight() override
	{
		if (IsHorizontal) {
			unsigned short MaxHeight = 0;
			mChildren.iterate(MaxHeightFunctor{MaxHeight});
			return MaxHeight;
		}
		else {
			unsigned short MaxHeight = 0;
			mChildren.iterate(MaxHeightFunctor{MaxHeight});
			return MaxHeight * mSize;
		}
	}

	struct DrawFunctor
	{
		template<typename T>
		void operator()(T & Child)
		{
			Child.draw();
		}
	};

	virtual void draw() override
	{
		mChildren.iterate(DrawFunctor{});
	}

	unsigned short getX() override
	{
		return mX;
	}

	unsigned short getY() override
	{
		return mY;
	}

	unsigned short getWidth() override
	{
		return mWidth;
	}

	unsigned short getHeight() override
	{
		return mHeight;
	}

	// Widget
	struct AquireMouseHorizontalFunctor
	{
		signed short X;
		signed short Y;

		template<typename T>
		bool operator()(T & Child)
		{
			signed short Max = Child.getX() + Child.getWidth();
			if (X < Max) {
				Child.aquireMouse(X, Y);
				return false;
			}
			return true;
		}
	};

	struct AquireMouseVerticalFunctor
	{
		signed short X;
		signed short Y;

		template<typename T>
		bool operator()(T & Child)
		{
			signed short Max = Child.getY() + Child.getHeight();
			if (Y < Max) {
				Child.aquireMouse(X, Y);
				return false;
			}
			return true;
		}
	};

	virtual void aquireMouse(signed short X, signed short Y) override
	{
		if (IsHorizontal) mChildren.iterateUntil(AquireMouseHorizontalFunctor{X, Y});
		else mChildren.iterateUntil(AquireMouseVerticalFunctor{X, Y});
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
