#pragma once

#include <cstdlib>
#include <ratio>

namespace twil {
namespace theme {

struct BoxFilter;

struct TentFilter;

template<typename RatioR>
struct QuadraticFilter;

using QuadraticInterpFilter = QuadraticFilter<std::ratio<1, 1>>;
using QuadraticApproxFilter = QuadraticFilter<std::ratio<5, 10>>;
using QuadraticMixFilter = QuadraticFilter<std::ratio<8, 10>>;

template<typename RatioB, typename RatioC>
struct CubicFilter;

using HermiteFilter = CubicFilter<std::ratio<0, 1>, std::ratio<0, 1>>;
using CatmullRomFilter = CubicFilter<std::ratio<0, 1>, std::ratio<1, 2>>;
using BSplineFilter = CubicFilter<std::ratio<1, 1>, std::ratio<0, 1>>;
using MitchellFilter = CubicFilter<std::ratio<1, 3>, std::ratio<1, 3>>;
using RobidouxFilter = CubicFilter<std::ratio<3782, 10000>, std::ratio<3901, 10000>>;
using RobidouxSharpFilter = CubicFilter<std::ratio<2620, 10000>, std::ratio<3690, 10000>>;

template<std::size_t Lobes>
struct LanczosFilter;

template<typename T>
struct ScaleTraits;

template<>
struct ScaleTraits<float>;

}
}
