#include "Size.hpp"

#include "Face.hpp"

#include FT_BBOX_H
#include FT_SIZES_H
#include <cmath>
#include <stdexcept>

namespace Twil {
namespace Ft {

SizeT::SizeT(FaceT & Face, FT_F26Dot6 Points, FT_UInt HorizontalDpi, FT_UInt VerticalDpi)
:
	mId{nullptr}
{
	auto Error = FT_New_Size(Face.mId, &mId);
	if (Error) throw std::runtime_error{"Unable to load font size"};

	FT_Activate_Size(mId);
	FT_Set_Char_Size(Face.mId, Points, Points, HorizontalDpi, VerticalDpi);
}

SizeT::~SizeT()
{
	FT_Done_Size(mId);
}

FT_Short SizeT::getHeight() const
{
	return mId->metrics.height;
}

FT_Short SizeT::getDescender() const
{
	return mId->metrics.descender;
}

FT_Short SizeT::getAscender() const
{
	return mId->metrics.ascender;
}

}
}
