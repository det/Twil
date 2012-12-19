#pragma once

#include "Ft/Face.hpp"
#include "Ft/Library.hpp"
#include "Ft/Size.hpp"
#include "Ui/Drawable.hpp"
#include "Ui/DrawableContainer.hpp"
#include "Ui/WindowBase.hpp"
#include "Theme/Label.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {

class WindowBase;

template<typename T>
class Label :
	public Drawable
{
	private:
	Ui::DrawableContainer & mParent;
	Ui::WindowBase & mBase;
	Theme::Label mThemeLabel;
	T mLayout;
	std::u32string mText;

	public:
	// Label
	Label(Ui::DrawableContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
		mParent{Parent},
		mBase{Base},
		mThemeLabel{Theme}
	{}

	void setText(std::u32string const & Text)
	{
		mText = Text;
		mThemeLabel.setText(Text);
		mBase.markNeedsRedraw();
	}

	// Drawable
	virtual void handleResized(unsigned short Width, unsigned short Height) override
	{
		mLayout.resize(Width, Height);
		auto LabelWidth = mThemeLabel.getWidth();
		auto LabelHeight = mThemeLabel.getHeight();
		auto X = mLayout.getLayoutX(LabelWidth);
		auto Y = mLayout.getLayoutY(LabelHeight);
		mThemeLabel.move(X, Y);
	}

	virtual void handleMoved(signed short X, signed short Y) override
	{
		mLayout.move(X, Y);
		auto LabelWidth = mThemeLabel.getWidth();
		auto LabelHeight = mThemeLabel.getHeight();
		auto LabelX = mLayout.getLayoutX(LabelWidth);
		auto LabelY = mLayout.getLayoutY(LabelHeight);
		mThemeLabel.move(LabelX, LabelY);
	}

	virtual unsigned short getFitWidth() override
	{
		return mThemeLabel.getWidth();
	}

	virtual unsigned short getFitHeight() override
	{
			return mThemeLabel.getHeight();
	}

	virtual void draw() override
	{
		if (mLayout.getHeight() == 0 || mLayout.getWidth() == 0) return;
		mThemeLabel.render();
	}

	virtual unsigned short getWidth() override
	{
		return mLayout.getWidth();
	}

	virtual unsigned short getHeight() override
	{
		return mLayout.getHeight();
	}

	virtual unsigned short getX() override
	{
		return mLayout.getX();
	}

	virtual unsigned short getY() override
	{
		return mLayout.getY();
	}
};

}
}
