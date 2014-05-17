#pragma once

#include "LabelFwd.hpp"


#include "Drawable.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Vertex/FillSolid.hpp"

#include <string>
#include <vector>

namespace Twil {
namespace Theme {

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
	Ui::WindowBaseT * mWindow;
	std::vector<LabelGlyph> mGlyphs;
	std::int16_t mWidth = 0;
	std::int16_t mHeight = 0;
	std::int32_t mLeft = 0.0f;
	std::int32_t mBottom = 0.0f;
	std::int32_t mClipLeft = 0.0f;
	std::int32_t mClipBottom = 0.0f;
	std::int32_t mClipRight = 0.0f;
	std::int32_t mClipTop = 0.0f;

public:
	LabelT() = default;
	void init(Ui::WindowBaseT & Window);

	/// \brief Sets the text to display.
	void setText(std::u32string const & Text);

	// Drawable
	void draw(Vertex::FillSolidT *) const final;

	// Widget
	void moveX(std::int32_t);
	void moveY(std::int32_t);

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

	std::int32_t getBaseWidth() const;
	std::int32_t getBaseHeight() const;
};

}
}
