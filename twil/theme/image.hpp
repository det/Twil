#pragma once

#include "image.hxx"

#include "drawable.hpp"
#include "ui/unit.hxx"
#include "ui/window_base.hxx"
#include "vertex/bitmap.hpp"

#include <cstdint>

namespace twil {
namespace theme {

/// \brief Responsible for drawing a Image.
class Image
:
	Drawable<vertex::Bitmap>
{
	Image(Image const &) = delete;
	Image & operator =(Image const &) = delete;

private:
	ui::WindowBase * window_;
	std::uint32_t offset_ = 0;
	std::uint16_t width_ = 0;
	std::uint16_t height_ = 0;
	ui::Dip left_ = 0;
	ui::Dip bottom_ = 0;
	ui::Dip clip_left_ = 0;
	ui::Dip clip_bottom_ = 0;
	ui::Dip clip_right_ = 0;
	ui::Dip clip_top_ = 0;

public:
	Image() = default;
	void Init(ui::WindowBase &);

	/// \brief Sets the text to display.
	void SetImage(char const *);

	// Drawable
	void Draw(vertex::Bitmap *) const final;

	// Widget
	void MoveX(ui::Dip);
	void MoveY(ui::Dip);

	void SetClipLeft(ui::Dip);
	void SetClipBottom(ui::Dip);
	void SetClipRight(ui::Dip);
	void SetClipTop(ui::Dip);

	ui::Dip GetLeft() const;
	ui::Dip GetBottom() const;
	ui::Dip GetRight() const;
	ui::Dip GetTop() const;

	ui::Dip GetClipLeft() const;
	ui::Dip GetClipRight() const;
	ui::Dip GetClipBottom() const;
	ui::Dip GetClipTop() const;

	ui::Dip GetBaseWidth() const;
	ui::Dip GetBaseHeight() const;
};

}
}
