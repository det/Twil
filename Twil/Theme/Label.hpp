#pragma once

#include "LabelFwd.hpp"

#include "Drawable.hpp"
#include "Ui/UnitFwd.hpp"
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
	Ui::PixelT mWidth = 0;
	Ui::PixelT mHeight = 0;
	Ui::DipT mLeft = 0.0f;
	Ui::DipT mBottom = 0.0f;
	Ui::DipT mClipLeft = 0.0f;
	Ui::DipT mClipBottom = 0.0f;
	Ui::DipT mClipRight = 0.0f;
	Ui::DipT mClipTop = 0.0f;

public:
	LabelT() = default;
	void init(Ui::WindowBaseT & Window);

	/// \brief Sets the text to display.
	void setText(std::u32string const & Text);

	// Drawable
	void draw(Vertex::FillSolidT *) const final;

	// Widget
	void moveX(Ui::DipT);
	void moveY(Ui::DipT);

	void setClipLeft(Ui::DipT);
	void setClipBottom(Ui::DipT);
	void setClipRight(Ui::DipT);
	void setClipTop(Ui::DipT);

	Ui::DipT getLeft() const;
	Ui::DipT getBottom() const;
	Ui::DipT getRight() const;
	Ui::DipT getTop() const;

	Ui::DipT getClipLeft() const;
	Ui::DipT getClipRight() const;
	Ui::DipT getClipBottom() const;
	Ui::DipT getClipTop() const;

	Ui::DipT getBaseWidth() const;
	Ui::DipT getBaseHeight() const;
};

}
}
