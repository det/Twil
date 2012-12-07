#pragma once

#include "Ft/Face.hpp"
#include "Ft/Library.hpp"
#include "Ft/Size.hpp"
#include "Ui/Drawable.hpp"
#include "Theme/Label.hpp"

#include <memory>
#include <string>

namespace Twil {

namespace Theme {
class Manager;
}

namespace Ui {
class WindowControl;

class Label : public Drawable {
	private:
	Ui::WindowControl & mControl;
	Theme::Label mThemeLabel;
	unsigned short mWidth;
	unsigned short mHeight;
	std::u32string mText;

	public:
	Label(Theme::Manager &, Ui::WindowControl &);

	virtual void handleResized(unsigned short, unsigned short);
	virtual void draw();

	void setText(std::u32string const &);
};

}
}
