#pragma once

#include "Vertex/OutlineGradient.hpp"

#include <vector>

namespace Twil {
namespace Theme {

class ManagerT;

/// \brief Responsible for drawing a button.
class ButtonT
{
	private:
	ManagerT & mManager;
	std::vector<Vertex::OutlineGradientT> mVertices;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mRight = 0;
	signed short mTop = 0;
	signed short mClipLeft = 0;
	signed short mClipBottom = 0;
	signed short mClipRight = 0;
	signed short mClipTop = 0;
	bool mIsDown = false;

	void clipLeft();
	void clipLeftCenter();
	void clipRight();
	void clipRightCenter();
	void clipBottom();
	void clipBottomCenter();
	void clipTop();
	void clipTopCenter();

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

	// Widget
	void moveX(signed short);
	void moveY(signed short);

	void resizeWidth(signed short);
	void resizeHeight(signed short);

	void setClipLeft(signed short);
	void setClipBottom(signed short);
	void setClipRight(signed short);
	void setClipTop(signed short);

	void draw() const;

	signed short getLeft() const;
	signed short getBottom() const;
	signed short getRight() const;
	signed short getTop() const;

	signed short getBaseWidth(signed short) const;
	signed short getBaseHeight(signed short) const;
};

}
}
