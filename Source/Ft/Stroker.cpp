#include "Ft/Stroker.hpp"

#include "Ft/Face.hpp"
#include "Ft/Library.hpp"
#include "Ft/Outline.hpp"

namespace Twil {
namespace Ft {

Stroker::Stroker(Ft::Library & Library)
{
	FT_Stroker_New(Library.mId, &mId);
}

Stroker::~Stroker()
{
	FT_Stroker_Done(mId);
}

void Stroker::clear()
{
	FT_Stroker_Rewind(mId);
}

void Stroker::setOptions(FT_Fixed Radius, FT_Stroker_LineCap LineCap, FT_Stroker_LineJoin LineJoin, FT_Fixed MiterLimit)
{
	FT_Stroker_Set(mId, Radius, LineCap, LineJoin, MiterLimit);
}

void Stroker::set(Ft::Outline & Outline)
{
	FT_Stroker_ParseOutline(mId, &Outline.mId, false);
}

void Stroker::set(Ft::Face & Face)
{
	FT_Stroker_ParseOutline(mId, &Face.mId->glyph->outline, false);
}
void Stroker::beginPath(FT_Vector A, FT_Bool IsOpen)
{
	FT_Stroker_BeginSubPath(mId, &A, IsOpen);
}

void Stroker::endPath()
{
	FT_Stroker_EndSubPath(mId);
}

void Stroker::addLine(FT_Vector B)
{
	FT_Stroker_LineTo(mId, &B);
}

void Stroker::addQuadratic(FT_Vector B, FT_Vector C)
{
	FT_Stroker_ConicTo(mId, &B, &C);
}

void Stroker::addCubic(FT_Vector B, FT_Vector C, FT_Vector D)
{
	FT_Stroker_CubicTo(mId, &B, &C, &D);
}

}
}
