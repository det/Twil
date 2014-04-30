#pragma once

#include "ButtonFwd.hpp"

#include "Drawable.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Vertex/OutlineGradient.hpp"

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
	float mLeft = 0.0f;
	float mBottom = 0.0f;
	float mRight = 0.0f;
	float mTop = 0.0f;
	float mClipLeft = 0.0f;
	float mClipBottom = 0.0f;
	float mClipRight = 0.0f;
	float mClipTop = 0.0f;
	bool mIsDown = false;

public:
	ButtonT() = default;
	void init(Ui::WindowBaseT &);

	/// \brief Sets whether the button is up or down.
	void setIsDown(bool IsDown);

	/// \returns The left margin for the theme.
	float getLeftMargin() const;

	/// \returns The right margin for the theme.
	float getRightMargin() const;

	/// \returns The bottom margin for the theme.
	float getBottomMargin() const;

	/// \returns The top margin for the theme.
	float getTopMargin() const;

	// Drawable
	void draw(Vertex::OutlineGradientT *) const final;

	// Widget
	void moveX(float);
	void moveY(float);

	void resizeWidth(float);
	void resizeHeight(float);

	void setClipLeft(float);
	void setClipBottom(float);
	void setClipRight(float);
	void setClipTop(float);

	float getLeft() const;
	float getBottom() const;
	float getRight() const;
	float getTop() const;

	float getClipLeft() const;
	float getClipRight() const;
	float getClipBottom() const;
	float getClipTop() const;

	float getBaseWidth(float) const;
	float getBaseHeight(float) const;
};

}
}
