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
	Label(Ui::DrawableContainer &, Theme::Manager &, Ui::WindowBase &);

	// Drawable
	virtual void handleResized(unsigned short, unsigned short) override;
	virtual void handleMoved(short, short) override;
	virtual unsigned short getFitWidth() override;
	virtual unsigned short getFitHeight() override;
	virtual void draw() override;

	virtual unsigned short getWidth() override { return mLayout.getWidth(); }
	virtual unsigned short getHeight() override { return mLayout.getHeight(); }
	virtual unsigned short getX() override { return mLayout.getX(); }
	virtual unsigned short getY() override { return mLayout.getY(); }

	// Label
	void setText(std::u32string const &);
};

template<typename T>
Label<T>::Label(Ui::DrawableContainer & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
	mParent{Parent},
	mBase{Base},
	mThemeLabel{Theme}
{}

template<typename T>
void Label<T>::setText(std::u32string const & Text)
{
	mText = Text;
	mThemeLabel.setText(Text);
	mBase.markNeedsRedraw();
}

template<typename T>
void Label<T>::handleResized(unsigned short Width, unsigned short Height)
{
	mLayout.resize(Width, Height);
	auto LabelWidth = mThemeLabel.getWidth();
	auto LabelHeight = mThemeLabel.getHeight();
	auto X = mLayout.getLayoutX(LabelWidth);
	auto Y = mLayout.getLayoutY(LabelHeight);
	mThemeLabel.move(X, Y);
}

template<typename T>
void Label<T>::handleMoved(short Width, short Height)
{
	mLayout.move(Width, Height);
	auto LabelWidth = mThemeLabel.getWidth();
	auto LabelHeight = mThemeLabel.getHeight();
	auto X = mLayout.getLayoutX(LabelWidth);
	auto Y = mLayout.getLayoutY(LabelHeight);
	mThemeLabel.move(X, Y);
}

template<typename T>
unsigned short Label<T>::getFitWidth()
{
	return mThemeLabel.getWidth();
}

template<typename T>
unsigned short Label<T>::getFitHeight()
{
	return mThemeLabel.getHeight();
}

template<typename T>
void Label<T>::draw()
{
	mThemeLabel.render();
}

}
}
