#include "Ft/Face.hpp"

#include "Ft/Library.hpp"
#include "Ft/Size.hpp"

#include FT_OUTLINE_H
#include FT_SIZES_H
#include <iostream>
#include <stdexcept>
#include <string>

namespace Twil {
namespace Ft {

Face::Face(Ft::Library & Library, std::string const & Path, FT_Long Index) :
	mLibrary{Library},
	mId{nullptr}
{
	auto Error = FT_New_Face(mLibrary.mId, Path.c_str(), Index, &mId);
	if (Error) throw std::runtime_error{"Unable to load font face"};
}

Face::~Face()
{
	FT_Done_Face(mId);
}

void Face::setActiveSize(Ft::Size const & Size)
{
	FT_Activate_Size(Size.mId);
}

FT_BBox Face::getCBox()
{
	FT_BBox Box;
	FT_Outline_Get_CBox(&mId->glyph->outline, &Box);
	return Box;
}

FT_Vector Face::getAdvance()
{
	return mId->glyph->advance;
}

FT_Pos Face::getLsbDelta()
{
	return mId->glyph->lsb_delta;
}

FT_Short Face::getHeight()
{
	return mId->size->metrics.height;
}

FT_Pos Face::getRsbDelta()
{
	return mId->glyph->rsb_delta;
}

FT_UInt Face::getCharIndex(char32_t Codepoint)
{
	return FT_Get_Char_Index(mId, Codepoint);
}

void Face::translate(FT_Pos X, FT_Pos Y)
{
	FT_Outline_Translate(&mId->glyph->outline, X, Y);
}

FT_Vector Face::getKerning(FT_UInt A, FT_UInt B)
{
	FT_Vector Delta;
	FT_Get_Kerning(mId, A, B, FT_KERNING_DEFAULT, &Delta);
	return Delta;
}

void Face::loadGlyph(FT_UInt Index)
{
	auto Error = FT_Load_Glyph(mId, Index, FT_LOAD_TARGET_NORMAL);
	if (Error != 0) throw std::runtime_error{"Unable to load glyph"};
}

void Face::loadGlyph(char32_t Codepoint)
{
	auto Index = FT_Get_Char_Index(mId, Codepoint);
	auto Error = FT_Load_Glyph(mId, Index, FT_LOAD_TARGET_NORMAL);
	if (Error != 0) throw std::runtime_error{"Unable to load glyph"};
}

}
}
