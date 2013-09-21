#pragma once

#include "KeyboardManager.hpp"
#include "MouseManager.hpp"
#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

class WindowBaseT
{
private:
	KeyboardManagerT mKeyboardManager;
	MouseManagerT mMouseManager;
	Theme::ManagerT mThemeManager;

public:
	KeyboardManagerT & getKeyboardManager();
	MouseManagerT & getMouseManager();
	Theme::ManagerT & getThemeManager();
};

}
}
