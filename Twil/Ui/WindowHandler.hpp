#pragma once

#include "WindowHandlerFwd.hpp"

#include "DipFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Ui {

class WindowHandlerT
{
public:
	virtual ~WindowHandlerT() = default;
	virtual void handleWindowExposed() {}
	virtual void handleWindowDeleted() {}
	virtual void handleWindowResizeWidth(DipT Width) {}
	virtual void handleWindowResizeHeight(DipT Height) {}
};

}
}
