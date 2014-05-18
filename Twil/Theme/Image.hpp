#pragma once

#include "ImageFwd.hpp"

#include "Drawable.hpp"
#include "Ui/UnitFwd.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Vertex/Bitmap.hpp"

#include <cstdint>

namespace Twil {
namespace Theme {

/// \brief Responsible for drawing a Image.
class ImageT
:
	DrawableT<Vertex::BitmapT>
{
	ImageT(ImageT const &) = delete;
	ImageT & operator =(ImageT const &) = delete;

private:
	Ui::WindowBaseT * mWindow;
	std::uint32_t mOffset = 0;
	std::uint16_t mWidth = 0;
	std::uint16_t mHeight = 0;
	Ui::DipT mLeft = 0;
	Ui::DipT mBottom = 0;
	Ui::DipT mClipLeft = 0;
	Ui::DipT mClipBottom = 0;
	Ui::DipT mClipRight = 0;
	Ui::DipT mClipTop = 0;

public:
	ImageT() = default;
	void init(Ui::WindowBaseT &);

	/// \brief Sets the text to display.
	void setImage(char const *);

	// Drawable
	void draw(Vertex::BitmapT *) const final;

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
