#pragma once

#include <cstdint>

namespace Twil {
namespace Ui {

class ContainerT;
class WindowBaseT;

class WidgetT
{
public:
	virtual ~WidgetT() {}

	/// \brief Initialize the widget
	virtual void init(ContainerT & Parent, WindowBaseT & Window) = 0;

	/// \brief Move the left and right position and clipping bounds.
	virtual void moveX(std::int16_t Delta) = 0;

	/// \brief Move the bottom and top position and clipping bounds.
	virtual void moveY(std::int16_t Delta) = 0;

	/// \brief Move the right position and clipping bound.
	virtual void resizeWidth(std::int16_t Delta) = 0;

	/// \brief Move the top position and clipping bound.
	virtual void resizeHeight(std::int16_t Delta) = 0;

	/// \brief Set the left clipping bound.
	virtual void setClipLeft(std::int16_t) = 0;

	/// \brief Set the right clipping bound.
	virtual void setClipRight(std::int16_t) = 0;

	/// \brief Set the bottom clipping bound.
	virtual void setClipBottom(std::int16_t) = 0;

	/// \brief Set the top clipping bound.
	virtual void setClipTop(std::int16_t) = 0;

	/// \returns The left position bound.
	virtual std::int16_t getLeft() const = 0;

	/// \returns The bottom position bound.
	virtual std::int16_t getBottom() const = 0;

	/// \returns The right position bound.
	virtual std::int16_t getRight() const = 0;

	/// \returns The top position bound.
	virtual std::int16_t getTop() const = 0;

	/// \returns The left clip line.
	virtual std::int16_t getClipLeft() const = 0;

	/// \returns The right clip line.
	virtual std::int16_t getClipRight() const = 0;

	/// \returns The bottom clip line.
	virtual std::int16_t getClipBottom() const = 0;

	/// \returns The top clip line.
	virtual std::int16_t getClipTop() const = 0;

	/// \returns The base width.
	virtual std::int16_t getBaseWidth() const = 0;

	/// \returns The base height.
	virtual std::int16_t getBaseHeight() const = 0;

	/// \brief Take control of the mouse or pass it to someone else.
	virtual void delegateMouse(std::int16_t X, std::int16_t Y) = 0;
};

}
}
