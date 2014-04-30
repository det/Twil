#pragma once

#include "BitmapFwd.hpp"

#include "Attribute/Offset1i.hpp"
#include "Attribute/Position2h.hpp"
#include "Attribute/Size2h.hpp"
#include "Attribute/Texcoord2h.hpp"

namespace Twil {
namespace Vertex {

struct BitmapT
{
	Attribute::Texcoord2hT ClipMin;
	Attribute::Texcoord2hT ClipMax;
	Attribute::Position2hT PositionMin;
	Attribute::Position2hT PositionMax;
	Attribute::Size2hT TextureSize;
	Attribute::Offset1iT Offset;

	static void setup();
};

}
}
