#include "FillSolid.hpp"

#include "Gl/Context.hpp"

#include <cstddef>

namespace Twil {
namespace Vertex {

void FillSolidT::setup()
{
	using VertexT = FillSolidT;
	using PointerT = GLvoid const *;

	auto Stride = sizeof(VertexT);
	auto ColorOffset = reinterpret_cast<PointerT>(offsetof(VertexT, Color));
	auto ClipMinOffset = reinterpret_cast<PointerT>(offsetof(VertexT, ClipMin));
	auto ClipMaxOffset = reinterpret_cast<PointerT>(offsetof(VertexT, ClipMax));
	auto PositionMinOffset = reinterpret_cast<PointerT>(offsetof(VertexT, PositionMin));
	auto PositionMaxOffset = reinterpret_cast<PointerT>(offsetof(VertexT, PositionMax));
	auto TextureSizeOffset = reinterpret_cast<PointerT>(offsetof(VertexT, TextureSize));
	auto OffsetOffset = reinterpret_cast<PointerT>(offsetof(VertexT, Offset));

	decltype(Color)::setup(0, Stride, ColorOffset);
	decltype(ClipMin)::setup(1, Stride, ClipMinOffset);
	decltype(ClipMax)::setup(2, Stride, ClipMaxOffset);
	decltype(PositionMin)::setup(3, Stride, PositionMinOffset);
	decltype(PositionMax)::setup(4, Stride, PositionMaxOffset);
	decltype(TextureSize)::setup(5, Stride, TextureSizeOffset);
	decltype(Offset)::setup(6, Stride, OffsetOffset);
}

}
}
