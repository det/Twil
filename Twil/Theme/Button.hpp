#pragma once

#include "ButtonFwd.hpp"

#include "Drawable.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <cstdint>

namespace Twil {
namespace Theme {

/// \brief Responsible for drawing a button.
class ButtonT
:
	public DrawableT<Vertex::OutlineGradientT>
{
	ButtonT(ButtonT const &) = delete;
	ButtonT & operator =(ButtonT const &) = delete;

private:
	Ui::WindowBaseT * mWindow;
	std::int32_t mLeft = 0.0f;
	std::int32_t mBottom = 0.0f;
	std::int32_t mRight = 0.0f;
	std::int32_t mTop = 0.0f;
	std::int32_t mClipLeft = 0.0f;
	std::int32_t mClipBottom = 0.0f;
	std::int32_t mClipRight = 0.0f;
	std::int32_t mClipTop = 0.0f;
	bool mIsDown = false;

public:
	ButtonT() = default;
	void init(Ui::WindowBaseT &);

	/// \brief Sets whether the button is up or down.
	void setIsDown(bool IsDown);

	/// \returns The left margin for the theme.
	std::int32_t getLeftMargin() const;

	/// \returns The right margin for the theme.
	std::int32_t getRightMargin() const;

	/// \returns The bottom margin for the theme.
	std::int32_t getBottomMargin() const;

	/// \returns The top margin for the theme.
	std::int32_t getTopMargin() const;

	// Drawable
	void draw(Vertex::OutlineGradientT *) const final;

	// Widget
	void moveX(std::int32_t);
	void moveY(std::int32_t);

	void resizeWidth(std::int32_t);
	void resizeHeight(std::int32_t);

	void setClipLeft(std::int32_t);
	void setClipBottom(std::int32_t);
	void setClipRight(std::int32_t);
	void setClipTop(std::int32_t);

	std::int32_t getLeft() const;
	std::int32_t getBottom() const;
	std::int32_t getRight() const;
	std::int32_t getTop() const;

	std::int32_t getClipLeft() const;
	std::int32_t getClipRight() const;
	std::int32_t getClipBottom() const;
	std::int32_t getClipTop() const;

	std::int32_t getBaseWidth(std::int32_t) const;
	std::int32_t getBaseHeight(std::int32_t) const;
};

}
}
