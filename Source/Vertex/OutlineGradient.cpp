#include "Vertex/OutlineGradient.hpp"

#include "Gl/Context.hpp"

#include <cstddef>

namespace Twil {
namespace Vertex {

void OutlineGradient::setup()
{
	auto Stride = sizeof(OutlineGradient);
	auto BorderColorOffset = (GLvoid const *) offsetof(OutlineGradient, BorderColor);
	auto TopColorOffset = (GLvoid const *) offsetof(OutlineGradient, TopColor);
	auto BottomColorOffset = (GLvoid const *) offsetof(OutlineGradient, BottomColor);
	auto InsideOffsetOffset = (GLvoid const *) offsetof(OutlineGradient, InsideOffset);
	auto OutsideOffsetOffset = (GLvoid const *) offsetof(OutlineGradient, OutsideOffset);
	auto PositionOffset = (GLvoid const *) offsetof(OutlineGradient, Position);
	auto SizeOffset = (GLvoid const *) offsetof(OutlineGradient, Size);
	auto ScaleOffset = (GLvoid const *) offsetof(OutlineGradient, Scale);

	Attribute::Color4b::setup(0, Stride, BorderColorOffset);
	Attribute::Color4b::setup(1, Stride, TopColorOffset);
	Attribute::Color4b::setup(2, Stride, BottomColorOffset);
	Attribute::Offset1i::setup(3, Stride, InsideOffsetOffset);
	Attribute::Offset1i::setup(4, Stride, OutsideOffsetOffset);
	Attribute::Position2h::setup(5, Stride, PositionOffset);
	Attribute::Size2h::setup(6, Stride, SizeOffset);
	Attribute::Size2h::setup(7, Stride, ScaleOffset);
}

}
}
