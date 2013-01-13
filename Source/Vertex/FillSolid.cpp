#include "Vertex/FillSolid.hpp"

#include "Gl/Context.hpp"

#include <cstddef>

namespace Twil {
namespace Vertex {

void FillSolid::setup()
{
	auto Stride = sizeof(FillSolid);
	auto ColorOffset = (GLvoid const *) offsetof(FillSolid, Color);
	auto OffsetOffset = (GLvoid const *) offsetof(FillSolid, Offset);
	auto PositionOffset = (GLvoid const *) offsetof(FillSolid, Position);
	auto SizeOffset = (GLvoid const *) offsetof(FillSolid, Size);
	auto ClipMinOffset = (GLvoid const *) offsetof(FillSolid, ClipMin);
	auto ClipMaxOffset = (GLvoid const *) offsetof(FillSolid, ClipMax);

	Attribute::Color4b::setup(0, Stride, ColorOffset);
	Attribute::Offset1i::setup(1, Stride, OffsetOffset);
	Attribute::Position2h::setup(2, Stride, PositionOffset);
	Attribute::Size2h::setup(3, Stride, SizeOffset);
	Attribute::Size2h::setup(4, Stride, ClipMinOffset);
	Attribute::Size2h::setup(5, Stride, ClipMaxOffset);
}

}
}
