#include "WindowBase.hpp"

namespace Twil {
namespace Ui {

KeyboardManagerT & WindowBaseT::getKeyboardManager()
{
	return mKeyboardManager;
}

MouseManagerT & WindowBaseT::getMouseManager()
{
	return mMouseManager;
}

Theme::ManagerT & WindowBaseT::getThemeManager()
{
	return mThemeManager;
}

}
}
