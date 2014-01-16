#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Texcoord2hT
{
	std::uint16_t S;
	std::uint16_t T;

	static void setup(std::uint32_t, std::int32_t, void const *);
};

}
}
