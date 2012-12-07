#pragma once

#include "Attribute/Color4b.hpp"
#include "Attribute/Offset1i.hpp"
#include "Attribute/Position2h.hpp"
#include "Attribute/Size2h.hpp"

#include <GL3/gl3.h>

#undef FillSolid

namespace Twil {
namespace Vertex {

struct FillSolid {
	Attribute::Color4b Color;
	Attribute::Offset1i Offset;
	Attribute::Position2h Position;
	Attribute::Size2h Size;

	static void setup();
};

}
}
