#include "Face.hpp"

#include "Library.hpp"
#include "Size.hpp"

#include FT_OUTLINE_H
#include FT_SIZES_H
#include <stdexcept>
#include <string>

namespace Twil {
namespace Ft {

FaceT::FaceT(LibraryT & Library, char const * Path, FT_Long Index) :
	mLibrary{&Library},
	mId{nullptr}
{
	auto Error = FT_New_Face(mLibrary->mId, Path, Index, &mId);
	if (Error) throw std::runtime_error{"Unable to load font face"};
}

FaceT::~FaceT()
{
	FT_Done_Face(mId);
}

void FaceT::setActiveSize(SizeT const & Size)
{
	FT_Activate_Size(Size.mId);
}

FT_BBox FaceT::getCBox() const
{
	FT_BBox Box;
	FT_Outline_Get_CBox(&mId->glyph->outline, &Box);
	return Box;
}

FT_Vector FaceT::getAdvance() const
{
	return mId->glyph->advance;
}

FT_Pos FaceT::getLsbDelta() const
{
	return mId->glyph->lsb_delta;
}

FT_Pos FaceT::getRsbDelta() const
{
	return mId->glyph->rsb_delta;
}

FT_UInt FaceT::getCharIndex(char32_t Codepoint) const
{
	return FT_Get_Char_Index(mId, Codepoint);
}

FT_Vector FaceT::getKerning(FT_UInt A, FT_UInt B) const
{
	FT_Vector Delta;
	FT_Get_Kerning(mId, A, B, FT_KERNING_DEFAULT, &Delta);
	return Delta;
}

void FaceT::translate(FT_Pos X, FT_Pos Y)
{
	FT_Outline_Translate(&mId->glyph->outline, X, Y);
}

void FaceT::loadGlyph(FT_UInt Index)
{
	auto Error = FT_Load_Glyph(mId, Index, FT_LOAD_TARGET_NORMAL);
	if (Error != 0) throw std::runtime_error{"Unable to load glyph"};
}

void FaceT::loadGlyph(char32_t Codepoint)
{
	auto Index = FT_Get_Char_Index(mId, Codepoint);
	auto Error = FT_Load_Glyph(mId, Index, FT_LOAD_TARGET_NORMAL);
	if (Error != 0) throw std::runtime_error{"Unable to load glyph"};
}

}
}
