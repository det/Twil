#pragma once

#include "OperatorFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Operator {

constexpr
std::int32_t operator"" _dips(long double Dips)
{
	return Dips * 65536;
}

constexpr
std::int32_t operator"" _dips(unsigned long long Dips)
{
	return Dips * 65536;
}

constexpr
std::int64_t operator"" _scale(long double Scale)
{
	return Scale * 4294967296;
}

constexpr
std::int64_t operator"" _scale(unsigned long long Scale)
{
	return Scale * 4294967296;
}

}
}
