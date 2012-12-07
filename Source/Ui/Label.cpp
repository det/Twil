#include "Ui/Label.hpp"

#include "Gl/Context.hpp"
#include "Ft/Face.hpp"
#include "Math/BarycentricInterpolator.hpp"
#include "Math/Matrix2.hpp"
#include "Ui/Window.hpp"

#include <iostream>

namespace Twil {
namespace Ui {

Label::Label(Theme::Manager & Theme, Ui::WindowControl & Control) :
	mControl{Control},
	mThemeLabel{Theme}
{
}

void Label::setText(std::u32string const & Text)
{
	mText = Text;
	mThemeLabel.setText(Text);
	mControl.setNeedsRedraw(true);
}

void Label::handleResized(unsigned short Width, unsigned short Height)
{
	mWidth = Width;
	mHeight = Height;
}

void Label::draw()
{
	mThemeLabel.render();
}

}
}
