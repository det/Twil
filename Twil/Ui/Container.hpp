#pragma once

#include <cstdint>

namespace Twil {
namespace Ui {

class ContainerT
{
public:
	virtual ~ContainerT() {}

	/// \brief Called from a child when it releases control of a mouse not within its bounds.
	virtual void releaseMouse(std::int16_t X, std::int16_t Y) = 0;

	/// \brief Called from a child when its base width changes.
	virtual void handleChildBaseWidthChanged(void *) = 0;

	/// \brief Called from a child when its base height changes.
	virtual void handleChildBaseHeightChanged(void *) = 0;
};

}
}
