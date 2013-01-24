#include "OutlineGradient.hpp"

#include "Gl/Context.hpp"

#include <cstddef>

namespace Twil {
namespace Vertex {

void OutlineGradientT::setup()
{
	using VertexT = OutlineGradientT;
	using PointerT = GLvoid const *;

	auto Stride = sizeof(VertexT);
	auto BorderColorOffset = reinterpret_cast<PointerT>(offsetof(VertexT, BorderColor));
	auto BottomColorOffset = reinterpret_cast<PointerT>(offsetof(VertexT, BottomColor));
	auto TopColorOffset = reinterpret_cast<PointerT>(offsetof(VertexT, TopColor));
	auto ClipMinOffset = reinterpret_cast<PointerT>(offsetof(VertexT, ClipMin));
	auto ClipMaxOffset = reinterpret_cast<PointerT>(offsetof(VertexT, ClipMax));
	auto PositionMinOffset = reinterpret_cast<PointerT>(offsetof(VertexT, PositionMin));
	auto PositionMaxOffset = reinterpret_cast<PointerT>(offsetof(VertexT, PositionMax));
	auto TextureSizeOffset = reinterpret_cast<PointerT>(offsetof(VertexT, TextureSize));
	auto InsideIndexOffset = reinterpret_cast<PointerT>(offsetof(VertexT, InsideIndex));
	auto OutsideIndexOffset = reinterpret_cast<PointerT>(offsetof(VertexT, OutsideIndex));

	decltype(BorderColor)::setup(0, Stride, BorderColorOffset);
	decltype(BottomColor)::setup(1, Stride, BottomColorOffset);
	decltype(TopColor)::setup(2, Stride, TopColorOffset);
	decltype(ClipMin)::setup(3, Stride, ClipMinOffset);
	decltype(ClipMax)::setup(4, Stride, ClipMaxOffset);
	decltype(PositionMin)::setup(5, Stride, PositionMinOffset);
	decltype(PositionMax)::setup(6, Stride, PositionMaxOffset);
	decltype(TextureSize)::setup(7, Stride, TextureSizeOffset);
	decltype(InsideIndex)::setup(8, Stride, InsideIndexOffset);
	decltype(OutsideIndex)::setup(9, Stride, OutsideIndexOffset);
}

}
}
