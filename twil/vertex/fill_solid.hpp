#pragma once

#include "fill_solid.hxx"

#include "attribute/color4b.hpp"
#include "attribute/offset1i.hpp"
#include "attribute/position2h.hpp"
#include "attribute/size2h.hpp"
#include "attribute/texcoord2h.hpp"

namespace twil {
namespace vertex {

struct FillSolid
{
	attribute::Color4B color;
	attribute::Texcoord2H clip_min;
	attribute::Texcoord2H clip_max;
	attribute::Position2H position_min;
	attribute::Position2H position_max;
	attribute::Size2H texture_size;
	attribute::Offset1I offset;

	static void Setup();
};

}
}
