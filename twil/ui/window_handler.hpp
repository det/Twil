#pragma once

#include "window_handler.hxx"

#include "unit.hxx"

#include <cstdint>

namespace twil {
namespace ui {

class WindowHandler
{
public:
	virtual ~WindowHandler() = default;
	virtual void HandleWindowExposed() {}
	virtual void HandleWindowDeleted() {}
	virtual void HandleWindowResizeWidth(Dip width) {}
	virtual void HandleWindowResizeHeight(Dip height) {}
};

}
}
