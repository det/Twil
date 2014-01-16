#include "OutlineGradient.hpp"

#include "Gl/Context.hpp"

#include <cstddef>

namespace Twil {
namespace Vertex {

void OutlineGradientT::setup()
{
	using VertexT = OutlineGradientT;
	using OffsetT = void const *;

	auto Stride = sizeof(VertexT);
	auto BorderColorOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, BorderColor));
	auto BottomColorOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, BottomColor));
	auto TopColorOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, TopColor));
	auto ClipMinOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, ClipMin));
	auto ClipMaxOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, ClipMax));
	auto PositionMinOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, PositionMin));
	auto PositionMaxOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, PositionMax));
	auto TextureSizeOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, TextureSize));
	auto InIndexOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, InIndex));
	auto OutIndexOffset = reinterpret_cast<OffsetT>(offsetof(VertexT, OutIndex));

	decltype(BorderColor)::setup(0, Stride, BorderColorOffset);
	decltype(BottomColor)::setup(1, Stride, BottomColorOffset);
	decltype(TopColor)::setup(2, Stride, TopColorOffset);
	decltype(ClipMin)::setup(3, Stride, ClipMinOffset);
	decltype(ClipMax)::setup(4, Stride, ClipMaxOffset);
	decltype(PositionMin)::setup(5, Stride, PositionMinOffset);
	decltype(PositionMax)::setup(6, Stride, PositionMaxOffset);
	decltype(TextureSize)::setup(7, Stride, TextureSizeOffset);
	decltype(InIndex)::setup(8, Stride, InIndexOffset);
	decltype(OutIndex)::setup(9, Stride, OutIndexOffset);
}

}
}
