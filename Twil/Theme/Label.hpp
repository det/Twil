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
	float mLeft = 0.0f;
	float mBottom = 0.0f;
	float mClipLeft = 0.0f;
	float mClipBottom = 0.0f;
	float mClipRight = 0.0f;
	float mClipTop = 0.0f;

public:
	LabelT() = default;
	void init(Ui::WindowBaseT & Window);

	/// \brief Sets the text to display.
	void setText(std::u32string const & Text);

	// Drawable
	void draw(Vertex::FillSolidT *) const final;

	// Widget
	void moveX(float);
	void moveY(float);

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

	float getBaseWidth() const;
	float getBaseHeight() const;
};

}
}
