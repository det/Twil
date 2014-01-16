#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Position2hT
{
	std::int16_t X;
	std::int16_t Y;

	static void setup(std::uint32_t, std::int32_t, void const *);
};

}
}
