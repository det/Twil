#include "Ft/Size.hpp"

#include "Ft/Face.hpp"

#include FT_BBOX_H
#include FT_SIZES_H
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace Twil {
namespace Ft {

Size::Size(Ft::Face & Face, FT_F26Dot6 Points) :
	mId{nullptr}
{
	auto Error = FT_New_Size(Face.mId, &mId);
	if (Error) throw std::runtime_error{"Unable to load font size"};

	FT_Activate_Size(mId);
	FT_Set_Char_Size(Face.mId, Points, Points, 96, 96);
}

Size::~Size()
{
	FT_Done_Size(mId);
}

FT_Short Size::getHeight()
{
	return mId->metrics.height;
}

FT_Short Size::getDescender()
{
	return mId->metrics.descender;
}

FT_Short Size::getAscender()
{
	return mId->metrics.ascender;
}

}
}
