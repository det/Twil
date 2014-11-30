#pragma once

#include "unit.hxx"

namespace twil {
namespace ui {
namespace udl {

constexpr
Dip operator"" _dip(long double dips)
{
	return dips * 65536;
}

constexpr
Dip operator"" _dip(unsigned long long dips)
{
	return dips * 65536;
}

}
}
}
