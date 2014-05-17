#pragma once

#include "DipFwd.hpp"

namespace Twil {
namespace Ui {
namespace Operator {

constexpr
DipT operator"" _dip(long double Dips)
{
	return Dips * 65536;
}

constexpr
DipT operator"" _dip(unsigned long long Dips)
{
	return Dips * 65536;
}

}
}
}
