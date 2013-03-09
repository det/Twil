#pragma once

namespace Twil {
namespace Ui {

class MouseManagerT;

class ContainerT
{
	public:
	virtual ~ContainerT() {}

	/// \brief Called from a child when it releases control of a mouse not within its bounds.
	virtual void releaseMouse(MouseManagerT &, signed short X, signed short Y) = 0;

	/// \brief Called from a child when its base width changes.
	virtual void handleChildBaseWidthChanged(void *) = 0;

	/// \brief Called from a child when its base height changes.
	virtual void handleChildBaseHeightChanged(void *) = 0;
};

}
}
