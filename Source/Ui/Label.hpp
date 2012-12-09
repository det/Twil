#pragma once

#include "Ft/Face.hpp"
#include "Ft/Library.hpp"
#include "Ft/Size.hpp"
#include "Ui/Drawable.hpp"
#include "Theme/Label.hpp"
#include "Ui/WindowControl.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {
class WindowControl;

template<typename T>
class Label :
	public Drawable
{
	private:
	Ui::WindowControl & mControl;
	Theme::Label mThemeLabel;
	T mLayout;
	std::u32string mText;

	public:
	Label(Theme::Manager &, Ui::WindowControl &);

	// Drawable
	virtual void handleResized(unsigned short, unsigned short);
	virtual void handleMoved(short, short);
	virtual unsigned short getFitWidth();
	virtual unsigned short getFitHeight();
	virtual void draw();

	void setText(std::u32string const &);
};

template<typename T>
Label<T>::Label(Theme::Manager & Theme, Ui::WindowControl & Control) :
	mControl{Control},
	mThemeLabel{Theme}
{
}

template<typename T>
void Label<T>::setText(std::u32string const & Text)
{
	mText = Text;
	mThemeLabel.setText(Text);
	mControl.setNeedsRedraw(true);
}

template<typename T>
void Label<T>::handleResized(unsigned short Width, unsigned short Height)
{
	mLayout.resize(Width, Height);
	auto LabelWidth = mThemeLabel.getWidth();
	auto LabelHeight = mThemeLabel.getHeight();
	auto X = mLayout.getX(LabelWidth);
	auto Y = mLayout.getY(LabelHeight);
	mThemeLabel.move(X, Y);
}

template<typename T>
void Label<T>::handleMoved(short Width, short Height)
{
	mLayout.move(Width, Height);
	auto LabelWidth = mThemeLabel.getWidth();
	auto LabelHeight = mThemeLabel.getHeight();
	auto X = mLayout.getX(LabelWidth);
	auto Y = mLayout.getY(LabelHeight);
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
