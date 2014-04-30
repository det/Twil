#pragma once

#include "WindowHandlerFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Ui {

class WindowHandlerT
{
public:
	virtual ~WindowHandlerT() = default;
	virtual void handleWindowExposed() {}
	virtual void handleWindowDeleted() {}
	virtual void handleWindowResizeWidth(float Width) {}
	virtual void handleWindowResizeHeight(float Height) {}
};

}
}
