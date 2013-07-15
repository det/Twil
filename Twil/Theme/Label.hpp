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
class LabelT
:
	DrawableT<Vertex::FillSolidT>
{
	LabelT(LabelT const &) = delete;
	LabelT & operator =(LabelT const &) = delete;

	private:	
	ManagerT * mManager;
	std::vector<LabelGlyph> mGlyphs;
	std::int16_t mLeft = 0;
	std::int16_t mBottom = 0;
	std::int16_t mWidth = 0;
	std::int16_t mHeight = 0;
	std::int16_t mClipLeft = 0;
	std::int16_t mClipBottom = 0;
	std::int16_t mClipRight = 0;
	std::int16_t mClipTop = 0;

	public:
	LabelT() = default;
	void init(ManagerT &);

	/// \brief Sets the text to display.
	void setText(std::u32string const & Text);

	// Drawable
	void draw(Vertex::FillSolidT *) const final;

	// Widget
	void moveX(std::int16_t);
	void moveY(std::int16_t);

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

	std::int16_t getBaseWidth() const;
	std::int16_t getBaseHeight() const;
};

}
}
