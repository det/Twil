#pragma once

#include "container.hxx"

#include "unit.hxx"

#include <cstdint>

namespace twil {
namespace ui {

class Container
{
public:
	virtual ~Container() = default;

	/// \brief Called from a child when it releases control of a mouse not within its bounds.
	virtual void ReleaseMouse(Dip x, Dip y) = 0;

	/// \brief Called from a child when its base width changes.
	virtual void HandleChildBaseWidthChanged(void *) = 0;

	/// \brief Called from a child when its base height changes.
	virtual void HandleChildBaseHeightChanged(void *) = 0;
};

}
}
