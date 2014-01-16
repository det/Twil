#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Offset1iT
{
	std::uint32_t Value;

	static void setup(std::uint32_t, std::int32_t, void const *);
};

}
}
