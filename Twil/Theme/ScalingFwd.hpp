#pragma once

#include <cstdlib>
#include <ratio>

namespace Twil {
namespace Theme {

struct BoxFilterT;

struct TentFilterT;

template<typename RatioRT>
struct QuadraticFilterT;

using QuadraticInterpFilterT = QuadraticFilterT<std::ratio<1, 1>>;
using QuadraticApproxFilterT = QuadraticFilterT<std::ratio<5, 10>>;
using QuadraticMixFilterT = QuadraticFilterT<std::ratio<8, 10>>;

template<typename RatioBT, typename RatioCT>
struct CubicFilterT;

using HermiteFilterT = CubicFilterT<std::ratio<0, 1>, std::ratio<0, 1>>;
using CatmullRomFilterT = CubicFilterT<std::ratio<0, 1>, std::ratio<1, 2>>;
using BSplineFilterT = CubicFilterT<std::ratio<1, 1>, std::ratio<0, 1>>;
using MitchellFilterT = CubicFilterT<std::ratio<1, 3>, std::ratio<1, 3>>;
using RobidouxFilterT = CubicFilterT<std::ratio<3782, 10000>, std::ratio<3901, 10000>>;
using RobidouxSharpFilterT = CubicFilterT<std::ratio<2620, 10000>, std::ratio<3690, 10000>>;

template<std::size_t Lobes>
struct LanczosFilterT;


}
}
