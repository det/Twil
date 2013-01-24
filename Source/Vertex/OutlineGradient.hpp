#pragma once

#include "Attribute/Color4b.hpp"
#include "Attribute/Offset1i.hpp"
#include "Attribute/Position2h.hpp"
#include "Attribute/Size2h.hpp"

#include <GL3/gl3.h>

namespace Twil {
namespace Vertex {

struct OutlineGradientT
{
	Attribute::Color4bT BorderColor;
	Attribute::Color4bT BottomColor;
	Attribute::Color4bT TopColor;
	Attribute::Position2hT ClipMin;
	Attribute::Position2hT ClipMax;
	Attribute::Position2hT PositionMin;
	Attribute::Position2hT PositionMax;
	Attribute::Size2hT TextureSize;
	Attribute::Offset1iT InsideIndex;
	Attribute::Offset1iT OutsideIndex;

	static void setup();
};

}
}
