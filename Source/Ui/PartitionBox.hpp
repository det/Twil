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
	public Ui::Widget<true, true>,
	public Ui::WidgetContainer<true, true>
{
	private:
	Ui::WidgetContainer<true, true> & mParent;
	Ui::Tuple<Args...> mChildren;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	static std::size_t const mSize = sizeof...(Args);

	public:
	// PartitionBox
	PartitionBox(Ui::WidgetContainer<true, true> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent(Parent), // Gcc bug prevents brace initialization syntax here
		mChildren{*this, Theme, Base}
	{}

	template<std::size_t I>
	typename Ui::TupleElement<I, Args...>::Type & getChild()
	{
		return Ui::TupleElement<I, Args...>().get(mChildren);
	}

	// Drawable
	struct SetXFunctor
	{
		signed short DeltaX;

		template<typename T>
		void operator()(T & Child)
		{
			auto ChildX = Child.getX();
			Child.setX(ChildX + DeltaX);
		}
	};

	virtual void setX(signed short X) override
	{
		signed short DeltaX = X - mX;
		mX = X;
		mChildren.iterate(SetXFunctor{DeltaX});
	}

	struct SetYFunctor
	{
		signed short DeltaY;

		template<typename T>
		void operator()(T & Child)
		{
			auto ChildY = Child.getY();
			Child.setY(ChildY + DeltaY);
		}
	};

	virtual void setY(signed short Y) override
	{
		signed short DeltaY = Y - mY;
		mY = Y;
		mChildren.iterate(SetYFunctor{DeltaY});
	}

	struct PartitionWidthFunctor
	{
		signed short X;
		unsigned short BoxWidth;
		unsigned short Mod;

		template<typename T>
		void operator()(T & Child)
		{
			unsigned short Width = BoxWidth;
			if (Mod > 0) {
				++Width;
				--Mod;
			}
			Child.setWidth(Width);
			Child.setX(X);
			X += Width;
		}
	};

	struct PartitionHeightFunctor
	{
		signed short Y;
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
			Child.setHeight(Height);
			Child.setY(Y);
			Y += Height;
		}
	};

	struct SetWidthFunctor
	{
		unsigned short Width;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setWidth(Width);
		}
	};

	struct SetHeightFunctor
	{
		unsigned short Height;

		template<typename T>
		void operator()(T & Child)
		{
			Child.setHeight(Height);
		}
	};

	virtual void setWidth(unsigned short Width) override
	{
		mWidth = Width;
		if (IsHorizontal) {
			unsigned short BoxWidth = mWidth / mSize;
			unsigned short Mod = mWidth % mSize;
			mChildren.iterate(PartitionWidthFunctor{mX, BoxWidth, Mod});
		}
		else {
			mChildren.iterate(SetWidthFunctor{mWidth});
		}
	}

	virtual void setHeight(unsigned short Height) override
	{
		mHeight = Height;
		if (IsHorizontal) {
			mChildren.iterate(SetHeightFunctor{mHeight});
		}
		else {
			unsigned short BoxHeight = mHeight / mSize;
			unsigned short Mod = mHeight % mSize;
			mChildren.iterate(PartitionHeightFunctor{mY, BoxHeight, Mod});
		}
	}

	virtual void setClipX(signed short, signed short) override
	{}

	virtual void setClipY(signed short, signed short) override
	{}

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
