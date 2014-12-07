#pragma once

#include "scaling.hxx"

#include <cmath>
#include <limits>
#include <memory>

namespace twil {
namespace theme {

struct BoxFilter
{
	static constexpr float support = 0.5f;

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > support) return 0.0f;

		return 1.0f;
	}
};

struct TentFilter
{
	static constexpr float support = 1.0f;

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > support) return 0.0f;

		return 1.0f - x;
	}
};

template<typename RatioR>
struct QuadraticFilter
{
	static constexpr float support = 1.5f;
	static constexpr float r = static_cast<float>(RatioR::num) / static_cast<float>(RatioR::den);

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > support) return 0.0f;

		float xx = x * x;
		if (x <= .5f) return (-2.0f * r) * xx + .5f * (r + 1.0f);
		else return (r * xx) + (-2.0f * r - .5f) * x + (3.0f / 4.0f) * (r + 1.0f);
	}
};

template<typename RatioB, typename RatioC>
struct CubicFilter
{
	static constexpr float support = 2.0f;
	static constexpr float b = static_cast<float>(RatioB::num) / static_cast<float>(RatioB::den);
	static constexpr float c = static_cast<float>(RatioC::num) / static_cast<float>(RatioC::den);

	float operator ()(float x) const
	{
		if (x < 0.0f) x = -x;
		if (x > support) return 0.0f;

		float xx = x * x;
		if (x < 1.0f)
		{
			x =
				(((12.0f - 9.0f * b - 6.0f * c) * (x * xx)) +
				((-18.0f + 12.0f * b + 6.0f * c) * xx) +
				(6.0f - 2.0f * b));
		}
		else
		{
			x =
				(((-1.0f * b - 6.0f * c) * (x * xx)) +
				((6.0f * b + 30.0f * c) * xx) +
				((-12.0f * b - 48.0f * c) * x) +
				(8.0f * b + 24.0f * c));
		}
		return x / 6.0f;
	}
};

template<std::size_t lobes>
struct LanczosFilter
{
	static constexpr float support = lobes;
	static constexpr float epsilon = .0000125f;
	static constexpr float pi = 3.141592653589793238462643383f;

	static float Clean(float x)
	{
		if (std::abs(x) < epsilon) return 0.0f;
		return x;
	}

	static float Sinc(float x)
	{
		x *= pi;
		if (x < 0.01f && x > -0.01f) return 1.0f + x * x * (-1.0f / 6.0f + x * x * 1.0f / 120.0f);
		else return std::sin(x) / x;
	}

	float operator ()(float x)
	{
		if (x < 0.0f) x = -x;
		if (x > support) return 0.0f;

		return Clean(Sinc(x) * Sinc(x / support));
	}
};

struct TapInfo
{
	float coord_factor;
	float scaled_support;
	float support_factor;
	std::size_t num_taps;
};

TapInfo MakeTapInfo(std::size_t source, std::size_t dest, float support)
{
	TapInfo info;
	info.coord_factor = static_cast<float>(source) / static_cast<float>(dest);

	float x;
	if (source > dest) x = info.coord_factor;
	else x = 1.0f;

	info.scaled_support = support * x;
	info.support_factor = 1.0f / x;
	info.num_taps = support * 2 * x + 0.9999875;
	return info;
}

struct Tap
{
	std::uint32_t index;
	float weight;
};

template<typename Filter>
void GenerateTapLists(
	std::size_t source, std::size_t dest,
	TapInfo info, Tap * samples, Filter filter)
{
	for (std::size_t coord = 0; coord != dest; ++coord)
	{
		auto center = (coord + 0.5f) * info.coord_factor - 0.5f;
		auto first = static_cast<std::int32_t>(std::floor(center - info.scaled_support + 1));
		float total_weight = 0.0f;
		for (std::size_t i = 0; i != info.num_taps; ++i)
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
				tap.weight = filter(distance * info.support_factor);
				total_weight += tap.weight;
			}
			samples[coord * info.num_taps + i] = tap;
		}

		for (std::size_t i = 0; i != info.num_taps; ++i)
		{
			samples[coord * info.num_taps + i].weight /= total_weight;
		}
	}
}

template<typename T>
struct ScaleTraits
{
	static_assert(std::numeric_limits<T>::is_integer, "Expected integer type");
	static_assert(!std::numeric_limits<T>::is_signed, "Expected unsigned type");

	static constexpr float max = std::numeric_limits<T>::max();

	static float ConvertFrom(T x)
	{
		return x / max;
	}

	static T ConvertTo(float x)
	{
		x = std::max(std::min(x, 1.0f), 0.0f);
		return x * max + 0.5f;
	}
};

template<>
struct ScaleTraits<float>
{
	static float ConvertFrom(float x)
	{
		return x;
	}

	static float ConvertTo(float x)
	{
		return x;
	}
};

template<typename Source, typename Dest>
void ScaleAxis(
	Source source, std::size_t source_width, std::size_t source_height,
	Dest dest, std::size_t dest_width,
	std::size_t channels, std::size_t num_taps, Tap const * tap_list)
{
	using SourceValue = typename std::iterator_traits<Source>::value_type;
	using DestValue = typename std::iterator_traits<Dest>::value_type;
	using SourceTraits = ScaleTraits<SourceValue>;
	using DestTraits = ScaleTraits<DestValue>;

	for (std::size_t dest_y = 0; dest_y != source_height; ++dest_y)
	{
		for (std::size_t dest_x = 0; dest_x != dest_width; ++dest_x)
		{
			for (std::size_t c = 0; c != channels; ++c)
			{
				float dest_channel = 0.0f;
				for (std::size_t i = 0; i != num_taps; ++i)
				{
					auto tap = tap_list[dest_x * num_taps + i];
					SourceValue x = source[dest_y * source_width * channels + tap.index * channels + c];
					dest_channel += SourceTraits::ConvertFrom(x) * tap.weight;
				}

				DestValue x = DestTraits::ConvertTo(dest_channel);
				dest[dest_x * source_height * channels + dest_y * channels + c] = x;
			}
		}
	}
}

template<typename Source, typename Dest, typename Filter>
void Scale(
	Source source, std::size_t source_width, std::size_t source_height,
	Dest dest, std::size_t dest_width, std::size_t dest_height,
	std::size_t channels, Filter filter)
{
	auto x_info = MakeTapInfo(source_width, dest_width, Filter::support);
	auto y_info = MakeTapInfo(source_height, dest_height, Filter::support);
	auto num_x_taps = x_info.num_taps;
	auto num_y_taps = y_info.num_taps;
	std::unique_ptr<Tap[]> x_taps{new Tap[num_x_taps * dest_width]};
	std::unique_ptr<Tap[]> y_taps{new Tap[num_y_taps * dest_height]};
	std::unique_ptr<float[]> x_data{new float[source_height * dest_width * channels]};
	auto x_taps_ptr = x_taps.get();
	auto y_taps_ptr = y_taps.get();
	auto x_data_ptr = x_data.get();

	GenerateTapLists(source_width, dest_width, x_info, x_taps_ptr, filter);
	GenerateTapLists(source_height, dest_height, y_info, y_taps_ptr, filter);
	ScaleAxis(source, source_width, source_height, x_data_ptr, dest_width, channels, num_x_taps, x_taps_ptr);
	ScaleAxis(x_data_ptr, source_height, dest_width, dest, dest_height, channels, num_y_taps, y_taps_ptr);
}

}
}
