#pragma once

#include "outline_gradient.hxx"

#include "attribute/color4b.hpp"
#include "attribute/offset1i.hpp"
#include "attribute/position2h.hpp"
#include "attribute/size2h.hpp"
#include "attribute/texcoord2h.hpp"

namespace twil {
namespace vertex {

struct OutlineGradient
{
	attribute::Color4B border_color;
	attribute::Color4B bottom_color;
	attribute::Color4B top_color;
	attribute::Texcoord2H clip_min;
	attribute::Texcoord2H clip_max;
	attribute::Position2H position_min;
	attribute::Position2H position_max;
	attribute::Size2H texture_size;
	attribute::Offset1I in_index;
	attribute::Offset1I out_index;

	static void Setup();
};

}
}
