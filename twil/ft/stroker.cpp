#include "stroker.hpp"

#include "face.hpp"
#include "library.hpp"
#include "outline.hpp"

namespace twil {
namespace ft {

Stroker::Stroker(Library & library)
{
	FT_Stroker_New(library.id_, &id_);
}

Stroker::~Stroker() noexcept
{
	FT_Stroker_Done(id_);
}

void Stroker::Clear()
{
	FT_Stroker_Rewind(id_);
}

void Stroker::SetOptions(
	FT_Fixed radius, FT_Stroker_LineCap line_cap,
	FT_Stroker_LineJoin line_join, FT_Fixed miter_limit)
{
	FT_Stroker_Set(id_, radius, line_cap, line_join, miter_limit);
}

void Stroker::Set(Outline & outline)
{
	FT_Stroker_ParseOutline(id_, &outline.id_, false);
}

void Stroker::Set(Face & face)
{
	FT_Stroker_ParseOutline(id_, &face.id_->glyph->outline, false);
}
void Stroker::BeginContour(FT_Vector a, FT_Bool is_open)
{
	FT_Stroker_BeginSubPath(id_, &a, is_open);
}

void Stroker::EndContour()
{
	FT_Stroker_EndSubPath(id_);
}

void Stroker::MoveLine(FT_Vector b)
{
	FT_Stroker_LineTo(id_, &b);
}

void Stroker::MoveQuadratic(FT_Vector b, FT_Vector c)
{
	FT_Stroker_ConicTo(id_, &b, &c);
}

void Stroker::MoveCubic(FT_Vector b, FT_Vector c, FT_Vector d)
{
	FT_Stroker_CubicTo(id_, &b, &c, &d);
}

}
}
