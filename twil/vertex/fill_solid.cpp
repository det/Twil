#include "fill_solid.hpp"

#include "gl/context.hpp"

#include <stddef.h>

namespace twil {
namespace vertex {

void FillSolid::Setup()
{
	using Vertex = FillSolid;
	using Offset = void const *;

	auto stride = sizeof(Vertex);
	auto color_offset = reinterpret_cast<Offset>(offsetof(Vertex, color));
	auto clip_min_offset = reinterpret_cast<Offset>(offsetof(Vertex, clip_min));
	auto clip_max_offset = reinterpret_cast<Offset>(offsetof(Vertex, clip_max));
	auto position_min_offset = reinterpret_cast<Offset>(offsetof(Vertex, position_min));
	auto position_max_offset = reinterpret_cast<Offset>(offsetof(Vertex, position_max));
	auto texture_size_offset = reinterpret_cast<Offset>(offsetof(Vertex, texture_size));
	auto offset_offset = reinterpret_cast<Offset>(offsetof(Vertex, offset));

	decltype(color)::Setup(0, stride, color_offset);
	decltype(clip_min)::Setup(1, stride, clip_min_offset);
	decltype(clip_max)::Setup(2, stride, clip_max_offset);
	decltype(position_min)::Setup(3, stride, position_min_offset);
	decltype(position_max)::Setup(4, stride, position_max_offset);
	decltype(texture_size)::Setup(5, stride, texture_size_offset);
	decltype(offset)::Setup(6, stride, offset_offset);
}

}
}
