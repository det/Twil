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
	virtual void handleWindowResizeWidth(std::int32_t Width) {}
	virtual void handleWindowResizeHeight(std::int32_t Height) {}
};

}
}
