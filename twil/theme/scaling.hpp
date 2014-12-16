#pragma once

#include "scaling.hxx"

#include <cmath>
#include <limits>
#include <memory>
#include <utility>

namespace twil {
namespace theme {

// Filters

struct BoxFilter
{
	static constexpr float kSupport = 0.5f;

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > kSupport) return 0.0f;

		return 1.0f;
	}
};

struct TentFilter
{
	static constexpr float kSupport = 1.0f;

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > kSupport) return 0.0f;

		return 1.0f - x;
	}
};

template<typename RatioR>
struct QuadraticFilter
{
	static constexpr float kSupport = 1.5f;
	static constexpr float kR = static_cast<float>(RatioR::num) / static_cast<float>(RatioR::den);

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > kSupport) return 0.0f;

		float xx = x * x;
		if (x <= .5f) return (-2.0f * kR) * xx + .5f * (kR + 1.0f);
		else return (kR * xx) + (-2.0f * kR - .5f) * x + (3.0f / 4.0f) * (kR + 1.0f);
	}
};

template<typename RatioB, typename RatioC>
struct CubicFilter
{
	static constexpr float kSupport = 2.0f;
	static constexpr float kB = static_cast<float>(RatioB::num) / static_cast<float>(RatioB::den);
	static constexpr float kC = static_cast<float>(RatioC::num) / static_cast<float>(RatioC::den);

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > kSupport) return 0.0f;

		float xx = x * x;
		if (x < 1.0f)
		{
			x =
				(((12.0f - 9.0f * kB - 6.0f * kC) * (x * xx)) +
				((-18.0f + 12.0f * kB + 6.0f * kC) * xx) +
				(6.0f - 2.0f * kB));
		}
		else
		{
			x =
				(((-1.0f * kB - 6.0f * kC) * (x * xx)) +
				((6.0f * kB + 30.0f * kC) * xx) +
				((-12.0f * kB - 48.0f * kC) * x) +
				(8.0f * kB + 24.0f * kC));
		}
		return x / 6.0f;
	}
};

template<std::size_t lobes>
struct LanczosFilter
{
	static constexpr float kSupport = lobes;
	static constexpr float kEpsilon = .0000125f;
	static constexpr float kPi = 3.141592653589793238462643383f;

	static float Clean(float x)
	{
		if (std::abs(x) < kEpsilon) return 0.0f;
		return x;
	}

	static float Sinc(float x)
	{
		x *= kPi;
		if (x < 0.01f && x > -0.01f) return 1.0f + x * x * (-1.0f / 6.0f + x * x * 1.0f / 120.0f);
		else return std::sin(x) / x;
	}

	float operator ()(float x)
	{
		if (x < 0.0f) x = -x;
		if (x > kSupport) return 0.0f;

		return Clean(Sinc(x) * Sinc(x / kSupport));
	}
};

// Data

template<typename T>
struct UnsignedData
{
	static_assert(std::numeric_limits<T>::is_integer, "Expected integer type");
	static_assert(!std::numeric_limits<T>::is_signed, "Expected unsigned type");

	static constexpr float kMax = std::numeric_limits<T>::max();
	using ValueT = T;

	static float ToFloat(ValueT x)
	{
		return x / kMax;
	}

	static ValueT FromFloat(float x)
	{
		x = std::max(std::min(x, 1.0f), 0.0f);
		return x * kMax + 0.5f;
	}
};

struct FloatData
{
	using ValueT = float;

	static float ToFloat(ValueT x)
	{
		return x;
	}

	static ValueT FromFloat(float x)
	{
		return x;
	}
};

// Channel

template<std::size_t index>
struct SrgbChannel
{
	static float FromLinear(float x)
	{
		if (x <= 0.0031308f) return 12.92f * x;
		else return 1.055f * pow(x, 0.41666f) - 0.055f;
	}

	static float ToLinear(float x)
	{
		if (x <= 0.04045f) return x / 12.92f;
		else return pow((x + 0.055f) / 1.055f, 2.4f);
	}

	template<typename Data, typename Source, typename Dest>
	static void ToFloat(Source source, Dest dest)
	{
		*dest = ToLinear(Data::ToFloat(source[index]));
	}

	template<typename Data, typename Source, typename Dest>
	static void FromFloat(Source source, Dest dest)
	{
		*dest = Data::FromFloat(FromLinear(source[index]));
	}

};

template<std::size_t index>
struct ScrgbChannel
{
	template<typename Data, typename Source, typename Dest>
	static void ToFloat(Source source, Dest dest)
	{
		*dest = Data::ToFloat(source[index]) * 8.0f - 0.5f;
	}

	template<typename Data, typename Source, typename Dest>
	static void FromFloat(Source source, Dest dest)
	{
		*dest = Data::FromFloat((source[index] + 0.5f) / 8.0f);
	}
};

template<std::size_t index>
struct LinearChannel
{
	template<typename Data, typename Source, typename Dest>
	static void ToFloat(Source source, Dest dest)
	{
		*dest = Data::ToFloat(source[index]);
	}

	template<typename Data, typename Source, typename Dest>
	static void FromFloat(Source source, Dest dest)
	{
		*dest = Data::FromFloat(source[index]);
	}
};

template<typename Ratio>
struct ConstantChannel
{
	static constexpr float kC = static_cast<float>(Ratio::num) / static_cast<float>(Ratio::den);

	template<typename Data, typename Source, typename Dest>
	static void ToFloat(Source source, Dest dest)
	{
		*dest = kC;
	}

	template<typename Data, typename Source, typename Dest>
	static void FromFloat(Source source, Dest dest)
	{
		*dest = Data::FromFloat(kC);
	}
};

// Format

template<typename Data, std::size_t input_stride, typename ... Channels>
struct UnpackedFormat
{
	using DataT = Data;
	static constexpr std::size_t kInputStride = input_stride;
	static constexpr std::size_t kOutputStride = sizeof...(Channels);

	template<std::size_t i, typename Source, typename Dest>
	void ReadFloatsHelper(Source source, Dest dest)
	{}

	template<std::size_t i, typename Source, typename Dest, typename C, typename ... Cs>
	void ReadFloatsHelper(Source source, Dest dest)
	{
		C::template ToFloat<Data>(source, dest + i);
		ReadFloatsHelper<i + 1, Source, Dest, Cs ...>(source, dest);
	}

	template<typename Source, typename Dest>
	void ReadFloats(Source source, Dest dest)
	{
		ReadFloatsHelper<0, Source, Dest, Channels ...>(source, dest);
	}

	template<std::size_t i, typename Source, typename Dest>
	void WriteFloatsHelper(Source source, Dest dest)
	{}

	template<std::size_t i, typename Source, typename Dest, typename C, typename ... Cs>
	void WriteFloatsHelper(Source source, Dest dest)
	{
		C::template FromFloat<Data>(source, dest + i);
		WriteFloatsHelper<i + 1, Source, Dest, Cs ...>(source, dest);
	}

	template<typename Source, typename Dest>
	void WriteFloats(Source source, Dest dest)
	{
		WriteFloatsHelper<0, Source, Dest, Channels ...>(source, dest);
	}
};

// Tap

struct Tap
{
	std::uint32_t index;
	float weight;
};

struct TapInfo
{
	float coord_factor;
	float scaled_support;
	float support_factor;
	std::size_t num_taps;
};

// Functions

TapInfo MakeTapInfo(std::size_t source, std::size_t dest, float support)
{
	TapInfo info;
	info.coord_factor = static_cast<float>(source) / static_cast<float>(dest);

	float x;
	if (source > dest) x = info.coord_factor;
	else x = 1.0f;

	info.scaled_support = support * x;
	info.support_factor = 1.0f / x;
	info.num_taps = support * 2.0f * x + 0.9999875f;
	return info;
}

template<typename Filter>
void GenerateTapLists(
	std::size_t source, std::size_t dest,
	float coord_factor, float scaled_support, float support_factor,
	std::size_t num_taps, Tap * samples,
	Filter filter)
{
	for (std::size_t coord = 0; coord != dest; ++coord)
	{
		auto center = (coord + 0.5f) * coord_factor - 0.5f;
		auto first = static_cast<std::int32_t>(std::floor(center - scaled_support + 1));
		float total_weight = 0.0f;
		for (std::size_t i = 0; i != num_taps; ++i)
		{
			Tap tap;
			std::int32_t index = first + i;
			std::int32_t min = 0;
			std::int32_t max = source - 1;
			if (index < min)
			{
				tap.index = 0;
				tap.weight = 0.0f;
			}
			else if (index > max)
			{
				tap.index = max;
				tap.weight = 0.0f;
			}
			else
			{
				tap.index = index;
				auto distance = center - tap.index;
				tap.weight = filter(distance * support_factor);
				total_weight += tap.weight;
			}
			samples[coord * num_taps + i] = tap;
		}

		for (std::size_t i = 0; i != num_taps; ++i)
		{
			samples[coord * num_taps + i].weight /= total_weight;
		}
	}
}

template<typename Source, typename Dest, typename SourceFormat, typename DestFormat>
void ScaleAxis(
	Source source, std::size_t source_width, std::size_t source_height,
	Dest dest, std::size_t dest_width,
	std::size_t num_taps, Tap const * tap_list,
	SourceFormat source_format, DestFormat dest_format)
{
	for (std::size_t y = 0; y != source_height; ++y)
	{
		for (std::size_t x = 0; x != dest_width; ++x)
		{
			std::array<float, SourceFormat::kOutputStride> dest_channels{};

			for (std::size_t i = 0; i != num_taps; ++i)
			{
				auto tap = tap_list[x * num_taps + i];
				auto offset_y = y * source_width * SourceFormat::kInputStride;
				auto offset_x = tap.index * SourceFormat::kInputStride;
				auto source_ptr = source + offset_y + offset_x;
				std::array<float, SourceFormat::kOutputStride> source_channels;
				source_format.ReadFloats(source_ptr, source_channels.data());

				for (std::size_t c = 0; c != SourceFormat::kOutputStride; ++c)
				{
					dest_channels[c] += source_channels[c] * tap.weight;
				}
			}

			auto offset_y = x * source_height * DestFormat::kOutputStride;
			auto offset_x = y * DestFormat::kOutputStride;
			auto dest_ptr = dest + offset_y + offset_x;
			dest_format.WriteFloats(dest_channels.data(), dest_ptr);
		}
	}
}

template<
	typename Source, typename Dest,
	typename SourceFormat, typename DestFormat>
void Convert(
	Source source, Dest dest, std::size_t size,
	SourceFormat source_format, DestFormat dest_format)
{
	for (std::size_t i = 0; i != size; ++i)
	{
		std::array<float, SourceFormat::kOutputStride> channels;
		source_format.ReadFloats(source + i * SourceFormat::kInputStride, channels.data());
		dest_format.WriteFloats(channels.data(), dest + i * DestFormat::kOutputStride);
	}
}

template<
	typename Source, typename Dest,
	typename SourceFormat, typename WorkingFormat, typename DestFormat,
	typename Filter>
void Scale(
	Source source, std::size_t source_width, std::size_t source_height,
	Dest dest, std::size_t dest_width, std::size_t dest_height,
	SourceFormat source_format, WorkingFormat working_format, DestFormat dest_format,
	Filter filter)
{
	static_assert(SourceFormat::kOutputStride == WorkingFormat::kInputStride, "");
	static_assert(WorkingFormat::kOutputStride == DestFormat::kInputStride, "");

	auto x_info = MakeTapInfo(source_width, dest_width, Filter::kSupport);
	auto y_info = MakeTapInfo(source_height, dest_height, Filter::kSupport);

	using ValueT = typename WorkingFormat::DataT::ValueT;
	std::size_t initial_size = source_height * source_width * WorkingFormat::kInputStride;
	std::size_t transposed_size = source_height * dest_width * WorkingFormat::kInputStride;
	std::unique_ptr<ValueT[]> initial{new ValueT[initial_size]};
	std::unique_ptr<ValueT[]> transposed{new ValueT[transposed_size]};
	std::unique_ptr<Tap[]> x_taps{new Tap[x_info.num_taps * dest_width]};
	std::unique_ptr<Tap[]> y_taps{new Tap[y_info.num_taps * dest_height]};

	Convert(
		source, initial.get(), source_height * source_width,
		source_format, working_format);

	GenerateTapLists(
		source_width, dest_width,
		x_info.coord_factor, x_info.scaled_support, x_info.support_factor,
		x_info.num_taps, x_taps.get(),
		filter);

	GenerateTapLists(
		source_height, dest_height,
		y_info.coord_factor, y_info.scaled_support, y_info.support_factor,
		y_info.num_taps, y_taps.get(),
		filter);

	ScaleAxis(
		initial.get(), source_width, source_height,
		transposed.get(), dest_width,
		x_info.num_taps, x_taps.get(),
		working_format, working_format);

	ScaleAxis(
		transposed.get(), source_height, dest_width,
		dest, dest_height,
		y_info.num_taps, y_taps.get(),
		working_format, dest_format);
}

}
}
