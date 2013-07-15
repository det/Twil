#pragma once

#include "Drawable.hpp"
#include "Manager.hpp"
#include "Settings.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <vector>

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
	ManagerT * mManager;
	std::int16_t mLeft = 0;
	std::int16_t mBottom = 0;
	std::int16_t mRight = 0;
	std::int16_t mTop = 0;
	std::int16_t mClipLeft = 0;
	std::int16_t mClipBottom = 0;
	std::int16_t mClipRight = 0;
	std::int16_t mClipTop = 0;
	bool mIsDown = false;

	static std::int16_t const mBorderSize = 1;
	static std::int16_t const mCornerSize = mBorderSize + Settings::Button::Roundness;

	public:
	ButtonT() = default;
	void init(ManagerT &);

	/// \brief Sets whether the button is up or down.
	void setIsDown(bool IsDown);

	/// \returns The left margin for the theme.
	std::int16_t getLeftMargin() const;

	/// \returns The right margin for the theme.
	std::int16_t getRightMargin() const;

	/// \returns The bottom margin for the theme.
	std::int16_t getBottomMargin() const;

	/// \returns The top margin for the theme.
	std::int16_t getTopMargin() const;

	// Drawable
	void draw(Vertex::OutlineGradientT *) const final;

	// Widget
	void moveX(std::int16_t);
	void moveY(std::int16_t);

	void resizeWidth(std::int16_t);
	void resizeHeight(std::int16_t);

	void setClipLeft(std::int16_t);
	void setClipBottom(std::int16_t);
	void setClipRight(std::int16_t);
	void setClipTop(std::int16_t);

	std::int16_t getLeft() const;
	std::int16_t getBottom() const;
	std::int16_t getRight() const;
	std::int16_t getTop() const;

	std::int16_t getClipLeft() const;
	std::int16_t getClipRight() const;
	std::int16_t getClipBottom() const;
	std::int16_t getClipTop() const;

	std::int16_t getBaseWidth(std::int16_t) const;
	std::int16_t getBaseHeight(std::int16_t) const;
};

}
}
