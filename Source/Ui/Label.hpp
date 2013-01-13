#pragma once

#include "Ui/Drawable.hpp"
#include "Ui/DrawableContainer.hpp"
#include "Theme/Label.hpp"

#include <iostream>
#include <string>

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {

class WindowBase;

class Label :
	public Drawable<false, false>
{
	private:
	Ui::DrawableContainer<false, false> & mParent;
	Ui::WindowBase & mBase;
	Theme::Label mThemeLabel;
	std::u32string mText;

	public:
	// Label
	Label(Ui::DrawableContainer<false, false> &, Theme::Manager &, Ui::WindowBase &);
	void setText(std::u32string const &);

	// Drawable
	virtual void setX(signed short) override;
	virtual void setY(signed short) override;
	virtual void setClipX(signed short, signed short) override;
	virtual void setClipY(signed short, signed short) override;

	virtual unsigned short getX() override;
	virtual unsigned short getY() override;
	virtual unsigned short getWidth() override;
	virtual unsigned short getHeight() override;
	virtual unsigned short getFitWidth() override;
	virtual unsigned short getFitHeight() override;

	virtual void draw() override;
};

}
}
