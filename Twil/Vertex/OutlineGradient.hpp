#pragma once

#include "Attribute/Color4b.hpp"
#include "Attribute/Offset1i.hpp"
#include "Attribute/Position2h.hpp"
#include "Attribute/Size2h.hpp"
#include "Attribute/Texcoord2h.hpp"

namespace Twil {
namespace Vertex {

struct OutlineGradientT
{
	Attribute::Color4bT BorderColor;
	Attribute::Color4bT BottomColor;
	Attribute::Color4bT TopColor;
	Attribute::Texcoord2hT ClipMin;
	Attribute::Texcoord2hT ClipMax;
	Attribute::Position2hT PositionMin;
	Attribute::Position2hT PositionMax;
	Attribute::Size2hT TextureSize;
	Attribute::Offset1iT InIndex;
	Attribute::Offset1iT OutIndex;

	static void setup();
};

}
}
