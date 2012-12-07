#pragma once

#include "Attribute/Color4b.hpp"
#include "Attribute/Offset1i.hpp"
#include "Attribute/Position2h.hpp"
#include "Attribute/Size2h.hpp"

#include <GL3/gl3.h>

namespace Twil {
namespace Vertex {

struct OutlineGradient {
	Attribute::Color4b BorderColor;
	Attribute::Color4b TopColor;
	Attribute::Color4b BottomColor;
	Attribute::Offset1i InsideOffset;
	Attribute::Offset1i OutsideOffset;
	Attribute::Position2h Position;
	Attribute::Size2h Size;
	Attribute::Size2h Scale;

	static void setup();
};

}
}
