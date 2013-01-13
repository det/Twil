#include "Ui/Label.hpp"

#include "Ui/WindowBase.hpp"

namespace Twil {
namespace Ui {

// Label
Label::Label(Ui::DrawableContainer<false, false> & Parent, Theme::Manager & Theme, Ui::WindowBase & Base) :
	mParent(Parent), // Gcc bug prevents brace initialization syntax here
	mBase(Base), // Gcc bug prevents brace initialization syntax here
	mThemeLabel{Theme}
{}

void Label::setText(std::u32string const & Text)
{
	mText = Text;
	mThemeLabel.setText(Text);
	mBase.markNeedsRedraw();
	mParent.handleChildWidthChanged();
}

// Drawable
void Label::setX(signed short X)
{
	mThemeLabel.setX(X);
}

void Label::setY(signed short Y)
{
	mThemeLabel.setY(Y);
}

void Label::setClipX(signed short Min, signed short Max)
{
	mThemeLabel.setClipX(Min, Max);
}

void Label::setClipY(signed short Min, signed short Max)
{
	mThemeLabel.setClipY(Min, Max);
}

unsigned short Label::getX()
{
	return mThemeLabel.getX();
}

unsigned short Label::getY()
{
	return mThemeLabel.getY();
}

unsigned short Label::getWidth()
{
	return mThemeLabel.getWidth();
}

unsigned short Label::getHeight()
{
	return mThemeLabel.getHeight();
}

unsigned short Label::getFitWidth()
{
	return mThemeLabel.getWidth();
}

unsigned short Label::getFitHeight()
{
	return mThemeLabel.getHeight();
}

void Label::draw()
{
	mThemeLabel.render();
}

}
}
