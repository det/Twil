#pragma once

#include "Vertex/FillSolid.hpp"

#include <string>
#include <vector>


namespace Twil {
namespace Theme {

class ManagerT;

/// \brief Responsible for drawing a label.
class LabelT
{
	private:
	ManagerT & mManager;
	std::vector<Vertex::FillSolidT> mVertices;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mRight = 0;
	signed short mTop = 0;
	short mClipLeft = 0;
	short mClipBottom = 0;
	short mClipRight = 0;
	short mClipTop = 0;

	public:
	LabelT(ManagerT &);

	/// \brief Sets the text to display.
	void setText(std::u32string const & Text);

	// Widget
	void moveX(signed short);
	void moveY(signed short);

	void setClipLeft(signed short);
	void setClipBottom(signed short);
	void setClipRight(signed short);
	void setClipTop(signed short);

	void draw() const;

	signed short getLeft() const;
	signed short getBottom() const;
	signed short getRight() const;
	signed short getTop() const;

	signed short getBaseWidth() const;
	signed short getBaseHeight() const;
};

}
}
