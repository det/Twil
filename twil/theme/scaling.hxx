#pragma once

#include <cstdlib>
#include <ratio>

namespace twil {
namespace theme {

// Filters

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

template<std::size_t lobes>
struct LanczosFilter;

// Data

template<typename T>
struct UnsignedData;

struct FloatData;

// Channels

template<std::size_t index>
struct SrgbChannel;

template<std::size_t index>
struct LinearChannel;

template<typename Ratio>
struct ConstantChannel;

using ZeroChannel = ConstantChannel<std::ratio<0, 1>>;
using OneChannel = ConstantChannel<std::ratio<1, 1>>;

// Format

template<typename Data, std::size_t input_stride, typename ... Channels>
struct UnpackedFormat;

template<typename T>
using Linear4Format = UnpackedFormat<
	T,
	4,
	LinearChannel<0>,
	LinearChannel<1>,
	LinearChannel<2>,
	LinearChannel<3>>;

template<typename T>
using Srgba3Linear1Format = UnpackedFormat<
	T,
	4,
	SrgbChannel<0>,
	SrgbChannel<1>,
	SrgbChannel<2>,
	LinearChannel<3>>;

template<typename T>
using Srgba4Format = UnpackedFormat<
	T,
	4,
	SrgbChannel<0>,
	SrgbChannel<1>,
	SrgbChannel<2>,
	SrgbChannel<3>>;

template<typename T>
using Linear3Format = UnpackedFormat<
	T,
	3,
	LinearChannel<0>,
	LinearChannel<1>,
	LinearChannel<2>>;

template<typename T>
using Srgba2Linear1Format = UnpackedFormat<
	T,
	3,
	SrgbChannel<0>,
	SrgbChannel<1>,
	LinearChannel<2>>;

template<typename T>
using Srgba3Format = UnpackedFormat<
	T,
	3,
	SrgbChannel<0>,
	SrgbChannel<1>,
	SrgbChannel<2>>;

template<typename T>
using Linear2Format = UnpackedFormat<
	T,
	2,
	LinearChannel<0>,
	LinearChannel<1>>;

template<typename T>
using Srgba1Linear1Format = UnpackedFormat<
	T,
	2,
	SrgbChannel<0>,
	LinearChannel<1>>;

template<typename T>
using Srgba2Format = UnpackedFormat<
	T,
	2,
	SrgbChannel<0>,
	SrgbChannel<1>>;

template<typename T>
using Linear1Format = UnpackedFormat<
	T,
	1,
	LinearChannel<0>>;

template<typename T>
using Srgba1Format = UnpackedFormat<
	T,
	1,
	SrgbChannel<0>>;

using Unsigned8Srgba3Linear1Format = Srgba3Linear1Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba3Linear1Format = Srgba3Linear1Format<UnsignedData<std::uint16_t>>;
using FloatSrgba3Linear1Format = Srgba3Linear1Format<FloatData>;
using Unsigned8Linear4Format = Linear4Format<UnsignedData<std::uint8_t>>;
using Unsigned16Linear4Format = Linear4Format<UnsignedData<std::uint16_t>>;
using FloatLinear4Format = Linear4Format<FloatData>;
using Unsigned8Srgba4Format = Srgba4Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba4Format = Srgba4Format<UnsignedData<std::uint16_t>>;
using FloatSrgba4Format = Srgba4Format<FloatData>;

using Unsigned8Srgba2Linear1Format = Srgba2Linear1Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba2Linear1Format = Srgba2Linear1Format<UnsignedData<std::uint16_t>>;
using FloatSrgba2Linear1Format = Srgba2Linear1Format<FloatData>;
using Unsigned8Linear3Format = Linear3Format<UnsignedData<std::uint8_t>>;
using Unsigned16Linear3Format = Linear3Format<UnsignedData<std::uint16_t>>;
using FloatLinear3Format = Linear3Format<FloatData>;
using Unsigned8Srgba3Format = Srgba3Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba3Format = Srgba3Format<UnsignedData<std::uint16_t>>;
using FloatSrgba3Format = Srgba3Format<FloatData>;

using Unsigned8Srgba1Linear1Format = Srgba1Linear1Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba1Linear1Format = Srgba1Linear1Format<UnsignedData<std::uint16_t>>;
using FloatSrgba1Linear1Format = Srgba1Linear1Format<FloatData>;
using Unsigned8Linear2Format = Linear2Format<UnsignedData<std::uint8_t>>;
using Unsigned16Linear2Format = Linear2Format<UnsignedData<std::uint16_t>>;
using FloatLinear2Format = Linear2Format<FloatData>;
using Unsigned8Srgba1Format = Srgba1Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba1Format = Srgba1Format<UnsignedData<std::uint16_t>>;
using FloatSrgba1Format = Srgba1Format<FloatData>;

using Unsigned8Srgba1Format = Srgba1Format<UnsignedData<std::uint8_t>>;
using Unsigned16Srgba1Format = Srgba1Format<UnsignedData<std::uint16_t>>;
using FloatSrgba1Format = Srgba1Format<FloatData>;
using Unsigned8Linear1Format = Linear1Format<UnsignedData<std::uint8_t>>;
using Unsigned16Linear1Format = Linear1Format<UnsignedData<std::uint16_t>>;
using FloatLinear1Format = Linear1Format<FloatData>;

// Tap

struct Tap;

struct TapInfo;

// Functions

TapInfo MakeTapInfo(std::size_t source, std::size_t dest, float support);

template<typename Filter>
void GenerateTapLists(
	std::size_t source, std::size_t dest,
	float coord_factor, float scaled_support, float support_factor,
	std::size_t num_taps, Tap * samples,
	Filter filter);

template<typename Source, typename Dest, typename SourceFormat, typename DestFormat>
void ScaleAxis(
	Source source, std::size_t source_width, std::size_t source_height,
	Dest dest, std::size_t dest_width,
	std::size_t num_taps, Tap const * tap_list,
	SourceFormat source_format, DestFormat dest_format);

template<
	typename Source, typename Dest,
	typename SourceFormat, typename TransposedFormat, typename DestFormat,
	typename Filter>
void Scale(
	Source source, std::size_t source_width, std::size_t source_height,
	Dest dest, std::size_t dest_width, std::size_t dest_height,
	SourceFormat source_format, TransposedFormat trandposed_format, DestFormat dest_format,
	Filter filter);

template<
	typename Source, typename Dest,
	typename SourceFormat, typename DestFormat>
void Convert(
	Source source, Dest dest, std::size_t size,
	SourceFormat source_format, DestFormat dest_format);

}
}
