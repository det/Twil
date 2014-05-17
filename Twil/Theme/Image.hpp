#pragma once

#include "ImageFwd.hpp"

#include "Drawable.hpp"
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
	std::int32_t mLeft = 0;
	std::int32_t mBottom = 0;
	std::int32_t mClipLeft = 0;
	std::int32_t mClipBottom = 0;
	std::int32_t mClipRight = 0;
	std::int32_t mClipTop = 0;

public:
	ImageT() = default;
	void init(Ui::WindowBaseT &);

	/// \brief Sets the text to display.
	void setImage(char const *);

	// Drawable
	void draw(Vertex::BitmapT *) const final;

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
