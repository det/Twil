#include "Bitmap.hpp"

#include "Gl/Context.hpp"

#include <cstddef>

namespace Twil {
namespace Vertex {

void BitmapT::setup()
{
	using VertexT = BitmapT;
	using PointerT = GLvoid const *;

	auto Stride = sizeof(VertexT);
	auto ClipMinOffset = reinterpret_cast<PointerT>(offsetof(VertexT, ClipMin));
	auto ClipMaxOffset = reinterpret_cast<PointerT>(offsetof(VertexT, ClipMax));
	auto PositionMinOffset = reinterpret_cast<PointerT>(offsetof(VertexT, PositionMin));
	auto PositionMaxOffset = reinterpret_cast<PointerT>(offsetof(VertexT, PositionMax));
	auto TextureSizeOffset = reinterpret_cast<PointerT>(offsetof(VertexT, TextureSize));
	auto OffsetOffset = reinterpret_cast<PointerT>(offsetof(VertexT, Offset));

	decltype(ClipMin)::setup(0, Stride, ClipMinOffset);
	decltype(ClipMax)::setup(1, Stride, ClipMaxOffset);
	decltype(PositionMin)::setup(2, Stride, PositionMinOffset);
	decltype(PositionMax)::setup(3, Stride, PositionMaxOffset);
	decltype(TextureSize)::setup(4, Stride, TextureSizeOffset);
	decltype(Offset)::setup(5, Stride, OffsetOffset);
}

}
}
