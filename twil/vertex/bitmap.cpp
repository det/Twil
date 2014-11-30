#include "bitmap.hpp"

#include "gl/context.hpp"

#include <stddef.h>

namespace twil {
namespace vertex {

void Bitmap::Setup()
{
	using Vertex = Bitmap;
	using Offset = void const *;

	auto stride = sizeof(Vertex);
	auto clip_min_offset = reinterpret_cast<Offset>(offsetof(Vertex, clip_min));
	auto clip_max_offset = reinterpret_cast<Offset>(offsetof(Vertex, clip_max));
	auto position_min_offset = reinterpret_cast<Offset>(offsetof(Vertex, position_min));
	auto position_max_offset = reinterpret_cast<Offset>(offsetof(Vertex, position_max));
	auto texture_size_offset = reinterpret_cast<Offset>(offsetof(Vertex, texture_size));
	auto offset_offset = reinterpret_cast<Offset>(offsetof(Vertex, offset));

	decltype(clip_min)::Setup(0, stride, clip_min_offset);
	decltype(clip_max)::Setup(1, stride, clip_max_offset);
	decltype(position_min)::Setup(2, stride, position_min_offset);
	decltype(position_max)::Setup(3, stride, position_max_offset);
	decltype(texture_size)::Setup(4, stride, texture_size_offset);
	decltype(offset)::Setup(5, stride, offset_offset);
}

}
}
