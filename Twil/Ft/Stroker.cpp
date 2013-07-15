#include "Stroker.hpp"

#include "Face.hpp"
#include "Library.hpp"
#include "Outline.hpp"

namespace Twil {
namespace Ft {

StrokerT::StrokerT(LibraryT & Library)
{
	FT_Stroker_New(Library.mId, &mId);
}

StrokerT::~StrokerT()
{
	FT_Stroker_Done(mId);
}

void StrokerT::clear()
{
	FT_Stroker_Rewind(mId);
}

void StrokerT::setOptions(
	FT_Fixed Radius, FT_Stroker_LineCap LineCap,
	FT_Stroker_LineJoin LineJoin, FT_Fixed MiterLimit)
{
	FT_Stroker_Set(mId, Radius, LineCap, LineJoin, MiterLimit);
}

void StrokerT::set(OutlineT & Outline)
{
	FT_Stroker_ParseOutline(mId, &Outline.mId, false);
}

void StrokerT::set(FaceT & Face)
{
	FT_Stroker_ParseOutline(mId, &Face.mId->glyph->outline, false);
}
void StrokerT::beginContour(FT_Vector A, FT_Bool IsOpen)
{
	FT_Stroker_BeginSubPath(mId, &A, IsOpen);
}

void StrokerT::endContour()
{
	FT_Stroker_EndSubPath(mId);
}

void StrokerT::moveLine(FT_Vector B)
{
	FT_Stroker_LineTo(mId, &B);
}

void StrokerT::moveQuadratic(FT_Vector B, FT_Vector C)
{
	FT_Stroker_ConicTo(mId, &B, &C);
}

void StrokerT::moveCubic(FT_Vector B, FT_Vector C, FT_Vector D)
{
	FT_Stroker_CubicTo(mId, &B, &C, &D);
}

}
}
