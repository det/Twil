#pragma once

#include "Drawable.hpp"
#include "Manager.hpp"
#include "Settings.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <vector>

namespace Twil {
namespace Theme {

/// \brief Responsible for drawing a button.
class ButtonT :
	public DrawableT<Vertex::OutlineGradientT>
{
	private:
	ManagerT & mManager;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mRight = 0;
	signed short mTop = 0;
	signed short mClipLeft = 0;
	signed short mClipBottom = 0;
	signed short mClipRight = 0;
	signed short mClipTop = 0;
	bool mIsDown = false;

	static signed short const mBorderSize = 1;
	static signed short const mCornerSize = mBorderSize + Settings::Button::Roundness;

	public:
	ButtonT(ManagerT &);

	/// \brief Sets whether the button is up or down.
	void setIsDown(bool IsDown);

	/// \returns The left margin for the theme
	signed short getLeftMargin() const;

	/// \returns The right margin for the theme
	signed short getRightMargin() const;

	/// \returns The bottom margin for the theme
	signed short getBottomMargin() const;

	/// \returns The top margin for the theme
	signed short getTopMargin() const;

	// Drawable
	void draw(Vertex::OutlineGradientT *) const final;

	// Widget
	void moveX(signed short);
	void moveY(signed short);

	void resizeWidth(signed short);
	void resizeHeight(signed short);

	void setClipLeft(signed short);
	void setClipBottom(signed short);
	void setClipRight(signed short);
	void setClipTop(signed short);

	signed short getLeft() const;
	signed short getBottom() const;
	signed short getRight() const;
	signed short getTop() const;

	signed short getBaseWidth(signed short) const;
	signed short getBaseHeight(signed short) const;
};

}
}
