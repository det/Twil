#include "size.hpp"

#include "face.hpp"

#include FT_BBOX_H
#include FT_SIZES_H
#include <cmath>
#include <stdexcept>

namespace twil {
namespace ft {

Size::Size(Face & face, FT_UInt width, FT_UInt height)
:
	id_{nullptr}
{
	auto error = FT_New_Size(face.id_, &id_);
	if (error) throw std::runtime_error{"Unable to load font size"};

	FT_Activate_Size(id_);
	FT_Set_Pixel_Sizes(face.id_, width, height);
}

Size::~Size() noexcept
{
	FT_Done_Size(id_);
}

FT_Short Size::GetHeight() const
{
	return id_->metrics.height;
}

FT_Short Size::GetDescender() const
{
	return id_->metrics.descender;
}

FT_Short Size::GetAscender() const
{
	return id_->metrics.ascender;
}

}
}
