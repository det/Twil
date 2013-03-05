#pragma once

#include "Drawable.hpp"
#include "Manager.hpp"
#include "Vertex/FillSolid.hpp"

#include <string>
#include <vector>

namespace Twil {
namespace Theme {

class ManagerT;

/// \brief Responsible for drawing a Image.
class ImageT :
	DrawableT<Vertex::BitmapT>
{
	private:	
	ManagerT & mManager;
	unsigned int mOffset = 0;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mWidth = 0;
	signed short mHeight = 0;
	short mClipLeft = 0;
	short mClipBottom = 0;
	short mClipRight = 0;
	short mClipTop = 0;

	public:
	ImageT(ManagerT &);

	/// \brief Sets the text to display.
	void setImage(char const *);

	// Drawable
	void draw(Vertex::BitmapT *) const final;

	// Widget
	void moveX(signed short);
	void moveY(signed short);

	void setClipLeft(signed short);
	void setClipBottom(signed short);
	void setClipRight(signed short);
	void setClipTop(signed short);

	signed short getLeft() const;
	signed short getBottom() const;
	signed short getRight() const;
	signed short getTop() const;

	signed short getBaseWidth() const;
	signed short getBaseHeight() const;
};

}
}
