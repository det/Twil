#pragma once

namespace Twil {
namespace Theme {

class ManagerT;

}
}

namespace Twil {
namespace Ui {

class ContainerT;
class WindowBaseT;

// WidgetT
class WidgetT
{
	public:
	virtual ~WidgetT() {}

	virtual void init(ContainerT & Parent, WindowBaseT & Window, Theme::ManagerT & Manager) = 0;

	/// \brief Move the left and right position and clipping bounds.
	virtual void moveX(signed short Delta) = 0;

	/// \brief Move the bottom and top position and clipping bounds.
	virtual void moveY(signed short Delta) = 0;

	/// \brief Move the right position and clipping bound.
	virtual void resizeWidth(signed short Delta) = 0;

	/// \brief Move the top position and clipping bound.
	virtual void resizeHeight(signed short Delta) = 0;

	/// \brief Set the left clipping bound.
	virtual void setClipLeft(signed short) = 0;

	/// \brief Set the right clipping bound.
	virtual void setClipRight(signed short) = 0;

	/// \brief Set the bottom clipping bound.
	virtual void setClipBottom(signed short) = 0;

	/// \brief Set the top clipping bound.
	virtual void setClipTop(signed short) = 0;

	/// \returns The left position bound.
	virtual signed short getLeft() const = 0;

	/// \returns The bottom position bound.
	virtual signed short getBottom() const = 0;

	/// \returns The right position bound.
	virtual signed short getRight() const = 0;

	/// \returns The top position bound.
	virtual signed short getTop() const = 0;

	/// \returns The left clip line.
	virtual signed short getClipLeft() const = 0;

	/// \returns The right clip line.
	virtual signed short getClipRight() const = 0;

	/// \returns The bottom clip line.
	virtual signed short getClipBottom() const = 0;

	/// \returns The top clip line.
	virtual signed short getClipTop() const = 0;

	/// \returns The base width.
	virtual signed short getBaseWidth() const = 0;

	/// \returns The base height.
	virtual signed short getBaseHeight() const = 0;

	/// \brief Take control of the mouse or pass it to someone else.
	virtual void delegateMouse(signed short, signed short) = 0;
};

}
}
