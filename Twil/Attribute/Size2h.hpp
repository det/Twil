#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Size2hT
{
	std::uint16_t Width;
	std::uint16_t Height;

	static void setup(std::uint32_t, std::int32_t, void const *);
};

}
}
