#pragma once

#include "ScalingFwd.hpp"

#include "Data/Memory.hpp"

#include <array>
#include <cmath>
#include <limits>

namespace Twil {
namespace Theme {

struct BoxFilterT
{
	static float constexpr Support = 0.5f;

	float operator ()(float X) const
	{
		return 1.0f;
	}
};

struct TentFilterT
{
	static float constexpr Support = 1.0f;

	float operator ()(float X) const
	{
		if (X < 0.0f) X = -X;
		return 1.0f - X;
	}
};

template<typename RatioRT>
struct QuadraticFilterT
{
	static float constexpr Support = 1.5f;
	static float constexpr R = static_cast<float>(RatioRT::num) / static_cast<float>(RatioRT::den);

	float operator ()(float X) const
	{
		if (X < 0.0f) X = -X;
		float XX = X * X;
		if (X <= .5f) return (-2.0f * R) * XX + .5f * (R + 1.0f);
		else return (R * XX) + (-2.0f * R - .5f) * X + (3.0f / 4.0f) * (R + 1.0f);
	}
};

template<typename RatioBT, typename RatioCT>
struct CubicFilterT
{
	static float constexpr Support = 2.0f;
	static float constexpr B = static_cast<float>(RatioBT::num) / static_cast<float>(RatioBT::den);
	static float constexpr C = static_cast<float>(RatioCT::num) / static_cast<float>(RatioCT::den);

	float operator ()(float X) const
	{
		float XX = X * X;

		if (X < 0.0f) X = -X;

		if (X < 1.0f)
		{
			X =
				(((12.0f - 9.0f * B - 6.0f * C) * (X * XX)) +
				((-18.0f + 12.0f * B + 6.0f * C) * XX) +
				(6.0f - 2.0f * B));

			return X / 6.0f;
		}
		else
		{
			X =
				(((-1.0f * B - 6.0f * C) * (X * XX)) +
				((6.0f * B + 30.0f * C) * XX) +
				((-12.0f * B - 48.0f * C) * X) +
				(8.0f * B + 24.0f * C));

			return X / 6.0f;
		}
	}
};

template<std::size_t Lobes>
struct LanczosFilterT
{
	static float constexpr Support = Lobes;

	static float clean(float X)
	{
	   float const Epsilon = .0000125f;
	   if (std::abs(X) < Epsilon) return 0.0f;
	   return X;
	}

	static float sinc(float X)
	{
		X *= std::atan(1) * 4;
		if (X < 0.01f && X > -0.01f) return 1.0f + X * X * (-1.0f / 6.0f + X * X * 1.0f / 120.0f);
		else return std::sin(X) / X;
	}

	float operator ()(float X) const
	{
		if (X < 0.0f) X = -X;
		return clean(sinc(X) * sinc(X / Support));
	}
};

struct TapT
{
	std::uint32_t Index;
	float Weight;
};

template<std::size_t NumTaps>
struct TapListT
{
	float Center;
	std::array<TapT, NumTaps> Taps;
};

template<std::size_t NumTaps, typename FilterT>
void generateTapLists(std::size_t Source, std::size_t Dest, TapListT<NumTaps> * Samples, FilterT const & Filter)
{
	float Ratio = static_cast<float>(Source) / static_cast<float>(Dest);

	for (std::size_t Coord = 0; Coord != Dest; ++Coord)
	{
		TapListT<NumTaps> Sample;
		Sample.Center = (Coord + 0.5f) * Ratio - 0.5f;
		std::size_t First = static_cast<int>(std::floor(Sample.Center - FilterT::Support + 1));

		float TotalWeight = 0.0f;

		for (std::size_t I = 0; I != NumTaps; ++I)
		{
			std::size_t Current = First + I;
			if (Current >= Source)
			{
				Sample.Taps[I].Index = 0;
				Sample.Taps[I].Weight = 0.0f;
				continue;
			}
			auto Distance = Sample.Center - Current;
			assert(std::abs(Distance) <= FilterT::Support);
			auto Weight = Filter(Distance);
			TotalWeight += Weight;
			Sample.Taps[I].Weight = Weight;
			Sample.Taps[I].Index = Current;
		}

		for (std::size_t I = 0; I != NumTaps; ++I)
		{
			Sample.Taps[I].Weight /= TotalWeight;
		}

		Samples[Coord] = Sample;
	}
}

template<typename SourceT, std::size_t NumTaps>
void resizeHorizontal(
	SourceT Source, std::size_t SourceWidth, std::size_t SourceHeight,
	float * Dest, std::size_t DestWidth,
	std::size_t Channels, TapListT<NumTaps> * Samples)
{
	float constexpr Max = std::numeric_limits<typename std::iterator_traits<SourceT>::value_type>::max();

	for (std::size_t DestY = 0; DestY != SourceHeight; ++DestY)
	{
		for (std::size_t DestX = 0; DestX != DestWidth; ++DestX)
		{
			auto Sample = Samples[DestX];
			for (std::size_t C = 0; C != Channels; ++C)
			{
				float DestChannel = 0.0f;
				for (std::size_t I = 0; I != NumTaps; ++I)
				{
					auto Tap = Sample.Taps[I];
					DestChannel += Source[DestY * SourceWidth * Channels + Tap.Index * Channels + C] / Max * Tap.Weight;
				}

				Dest[DestY * DestWidth * Channels + DestX * Channels + C] = DestChannel;
			}
		}
	}
}

template<typename DestT, std::size_t NumTaps>
void resizeVertical(
	float * Source,
	DestT Dest, std::size_t DestWidth, std::size_t DestHeight,
	std::size_t Channels, TapListT<NumTaps> * Samples)
{
	float constexpr Max = std::numeric_limits<typename std::iterator_traits<DestT>::value_type>::max();

	for (std::size_t DestY = 0; DestY != DestHeight; ++DestY)
	{
		for (std::size_t DestX = 0; DestX != DestWidth; ++DestX)
		{
			auto Sample = Samples[DestY];
			for (std::size_t C = 0; C != Channels; ++C)
			{
				float DestChannel = 0.0f;
				for (std::size_t I = 0; I != NumTaps; ++I)
				{
					auto Tap = Sample.Taps[I];
					DestChannel += Source[Tap.Index * DestWidth * Channels + DestX * Channels + C] * Tap.Weight;
				}

				if (DestChannel > 1.0f) DestChannel = 1.0f;
				if (DestChannel < 0.0f) DestChannel = 0.0f;
				Dest[DestY * DestWidth * Channels + DestX * Channels + C] = DestChannel * Max + 0.5f;
			}
		}
	}
}

template<typename FilterT, typename SourceT, typename DestT>
void scaleUp(
	SourceT Source, std::size_t SourceWidth, std::size_t SourceHeight,
	DestT Dest, std::size_t DestWidth, std::size_t DestHeight,
	std::size_t Channels, FilterT const & Filter = {})
{
	std::size_t constexpr NumTaps = FilterT::Support * 2;
	auto HorizData = Data::makeUniqueArray<float>(SourceHeight * DestWidth * Channels);
	auto HorizSamples = Data::makeUniqueArray<TapListT<NumTaps>>(DestWidth);
	auto VertSamples = Data::makeUniqueArray<TapListT<NumTaps>>(DestHeight);

	generateTapLists(SourceWidth, DestWidth, HorizSamples.get(), Filter);
	generateTapLists(SourceHeight, DestHeight, VertSamples.get(), Filter);
	resizeHorizontal(Source, SourceWidth, SourceHeight, HorizData.get(), DestWidth, Channels, HorizSamples.get());
	resizeVertical(HorizData.get(), Dest, DestWidth, DestHeight, Channels, VertSamples.get());
}

}
}