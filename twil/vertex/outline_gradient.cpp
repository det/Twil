#include "outline_gradient.hpp"

#include "gl/context.hpp"

#include <stddef.h>

namespace twil {
namespace vertex {

void OutlineGradient::Setup()
{
	using Vertex = OutlineGradient;
	using Offset = void const *;

	auto stride = sizeof(Vertex);
	auto border_color_offset = reinterpret_cast<Offset>(offsetof(Vertex, border_color));
	auto bottom_color_offset = reinterpret_cast<Offset>(offsetof(Vertex, bottom_color));
	auto top_color_offset = reinterpret_cast<Offset>(offsetof(Vertex, top_color));
	auto clip_min_offset = reinterpret_cast<Offset>(offsetof(Vertex, clip_min));
	auto clip_max_offset = reinterpret_cast<Offset>(offsetof(Vertex, clip_max));
	auto position_min_offset = reinterpret_cast<Offset>(offsetof(Vertex, position_min));
	auto position_max_offset = reinterpret_cast<Offset>(offsetof(Vertex, position_max));
	auto texture_size_offset = reinterpret_cast<Offset>(offsetof(Vertex, texture_size));
	auto in_index_offset = reinterpret_cast<Offset>(offsetof(Vertex, in_index));
	auto out_index_offset = reinterpret_cast<Offset>(offsetof(Vertex, out_index));

	decltype(border_color)::Setup(0, stride, border_color_offset);
	decltype(bottom_color)::Setup(1, stride, bottom_color_offset);
	decltype(top_color)::Setup(2, stride, top_color_offset);
	decltype(clip_min)::Setup(3, stride, clip_min_offset);
	decltype(clip_max)::Setup(4, stride, clip_max_offset);
	decltype(position_min)::Setup(5, stride, position_min_offset);
	decltype(position_max)::Setup(6, stride, position_max_offset);
	decltype(texture_size)::Setup(7, stride, texture_size_offset);
	decltype(in_index)::Setup(8, stride, in_index_offset);
	decltype(out_index)::Setup(9, stride, out_index_offset);
}

}
}
