#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Color4bT
{
	std::uint8_t Red;
	std::uint8_t Green;
	std::uint8_t Blue;
	std::uint8_t Alpha;

	static void setup(std::uint32_t, std::int32_t, void const *);
};

Color4bT mix(Color4bT const &, Color4bT const &, std::uint16_t);

}
}
