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
class ImageT
:
	DrawableT<Vertex::BitmapT>
{
	ImageT(ImageT const &) = delete;
	ImageT & operator =(ImageT const &) = delete;

private:
	ManagerT * mManager;
	std::uint32_t mOffset = 0;
	std::uint16_t mWidth = 0;
	std::uint16_t mHeight = 0;
	float mLeft = 0;
	float mBottom = 0;
	float mClipLeft = 0;
	float mClipBottom = 0;
	float mClipRight = 0;
	float mClipTop = 0;

public:
	ImageT() = default;
	void init(ManagerT &);

	/// \brief Sets the text to display.
	void setImage(char const *);

	// Drawable
	void draw(Vertex::BitmapT *) const final;

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
