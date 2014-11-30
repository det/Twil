#include "face.hpp"

#include "library.hpp"
#include "size.hpp"

#include FT_OUTLINE_H
#include FT_SIZES_H
#include <stdexcept>
#include <string>

namespace twil {
namespace ft {

Face::Face(Library & library, char const * path, FT_Long index)
:
	library_{&library},
	id_{nullptr}
{
	auto error = FT_New_Face(library_->id_, path, index, &id_);
	if (error) throw std::runtime_error{"Unable to load font face"};
}

Face::~Face() noexcept
{
	FT_Done_Face(id_);
}

void Face::SetActiveSize(Size const & size)
{
	FT_Activate_Size(size.id_);
}

FT_BBox Face::GetCBox() const
{
	FT_BBox box;
	FT_Outline_Get_CBox(&id_->glyph->outline, &box);
	return box;
}

FT_Vector Face::GetAdvance() const
{
	return id_->glyph->advance;
}

FT_Pos Face::GetLsbDelta() const
{
	return id_->glyph->lsb_delta;
}

FT_Pos Face::GetRsbDelta() const
{
	return id_->glyph->rsb_delta;
}

FT_UInt Face::GetCharIndex(char32_t codepoint) const
{
	return FT_Get_Char_Index(id_, codepoint);
}

FT_Vector Face::GetKerning(FT_UInt a, FT_UInt b) const
{
	FT_Vector delta;
	FT_Get_Kerning(id_, a, b, FT_KERNING_DEFAULT, &delta);
	return delta;
}

void Face::Translate(FT_Pos x, FT_Pos y)
{
	FT_Outline_Translate(&id_->glyph->outline, x, y);
}

void Face::LoadGlyph(FT_UInt index)
{
	auto error = FT_Load_Glyph(id_, index, FT_LOAD_TARGET_NORMAL);
	if (error != 0) throw std::runtime_error{"Unable to load glyph"};
}

void Face::LoadGlyph(char32_t codepoint)
{
	auto index = FT_Get_Char_Index(id_, codepoint);
	auto error = FT_Load_Glyph(id_, index, FT_LOAD_TARGET_NORMAL);
	if (error != 0) throw std::runtime_error{"Unable to load glyph"};
}

}
}
