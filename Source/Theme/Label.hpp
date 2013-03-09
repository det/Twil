#pragma once

#include "Drawable.hpp"
#include "Manager.hpp"
#include "Vertex/FillSolid.hpp"

#include <string>
#include <vector>

namespace Twil {
namespace Theme {

class ManagerT;

struct LabelGlyph
{
	Attribute::Position2hT PositionMin;
	Attribute::Position2hT PositionMax;
	Attribute::Size2hT TextureSize;
	Attribute::Offset1iT Offset;
};

/// \brief Responsible for drawing a label.
class LabelT :
	DrawableT<Vertex::FillSolidT>
{
	private:	
	ManagerT * mManager;
	std::vector<LabelGlyph> mGlyphs;
	signed short mLeft = 0;
	signed short mBottom = 0;
	signed short mWidth = 0;
	signed short mHeight = 0;
	short mClipLeft = 0;
	short mClipBottom = 0;
	short mClipRight = 0;
	short mClipTop = 0;

	public:
	void init(ManagerT &);

	/// \brief Sets the text to display.
	void setText(std::u32string const & Text);

	// Drawable
	void draw(Vertex::FillSolidT *) const final;

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

	signed short getClipLeft() const;
	signed short getClipRight() const;
	signed short getClipBottom() const;
	signed short getClipTop() const;

	signed short getBaseWidth() const;
	signed short getBaseHeight() const;
};

}
}
