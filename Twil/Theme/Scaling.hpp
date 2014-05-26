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
		if (X < 0.0f) X = -X;
		if (X > Support) return 0.0f;

		return 1.0f;
	}
};

struct TentFilterT
{
	static float constexpr Support = 1.0f;

	float operator ()(float X) const
	{
		if (X < 0.0f) X = -X;
		if (X > Support) return 0.0f;

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
		if (X > Support) return 0.0f;

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
		if (X < 0.0f) X = -X;
		if (X > Support) return 0.0f;

		float XX = X * X;
		if (X < 1.0f)
		{
			X =
				(((12.0f - 9.0f * B - 6.0f * C) * (X * XX)) +
				((-18.0f + 12.0f * B + 6.0f * C) * XX) +
				(6.0f - 2.0f * B));
		}
		else
		{
			X =
				(((-1.0f * B - 6.0f * C) * (X * XX)) +
				((6.0f * B + 30.0f * C) * XX) +
				((-12.0f * B - 48.0f * C) * X) +
				(8.0f * B + 24.0f * C));
		}
		return X / 6.0f;
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
		if (X > Support) return 0.0f;

		return clean(sinc(X) * sinc(X / Support));
	}
};

template<std::size_t NumTaps>
struct alignas(16) TapListT
{
	std::array<float, NumTaps> Weights;
	float Center;
	std::size_t First;
};

template<std::size_t NumTaps, typename FilterT>
void generateTapLists(std::size_t Source, std::size_t Dest, TapListT<NumTaps> * Samples, FilterT const & Filter)
{
	float Ratio = static_cast<float>(Source) / static_cast<float>(Dest);

	for (std::size_t Coord = 0; Coord != Dest; ++Coord)
	{
		TapListT<NumTaps> Sample;
		Sample.Center = (Coord + 0.5f) * Ratio - 0.5f;
		Sample.First = static_cast<int>(std::floor(Sample.Center - FilterT::Support + 1));
		if (Sample.First > Source) Sample.First = 0;
		else if (Sample.First + NumTaps > Source) Sample.First = Source - NumTaps;

		float TotalWeight = 0.0f;
		for (std::size_t I = 0; I != NumTaps; ++I)
		{
			std::size_t Current = Sample.First + I;
			float Weight = Filter(Sample.Center - Current);
			TotalWeight += Weight;
			Sample.Weights[I] = Weight;
		}

		for (std::size_t I = 0; I != NumTaps; ++I)
		{
			Sample.Weights[I] /= TotalWeight;
		}

		Samples[Coord] = Sample;
	}
}

template<typename T>
struct ScaleTraitsT
{
	static_assert(std::numeric_limits<T>::is_integer, "Expected integer type");
	static_assert(!std::numeric_limits<T>::is_signed, "Expected unsigned type");

	static constexpr float Max = std::numeric_limits<T>::max();

	static float convertFrom(T X)
	{
		return X / Max;
	}

	static T convertTo(float X)
	{
		X = std::max(std::min(X, 1.0f), 0.0f);
		return X * Max + 0.5f;
	}
};

template<>
struct ScaleTraitsT<float>
{
	static float convertFrom(float X)
	{
		return X;
	}

	static float convertTo(float X)
	{
		return X;
	}
};

template<typename SourceT, typename DestT, std::size_t NumTaps>
void scaleAxis(
	SourceT Source, std::size_t SourceWidth, std::size_t SourceHeight,
	DestT Dest, std::size_t DestWidth,
	std::size_t Channels, TapListT<NumTaps> * TapLists)
{
	using SourceValueT = typename std::iterator_traits<SourceT>::value_type;
	using DestValueT = typename std::iterator_traits<DestT>::value_type;
	using SourceTraitsT = ScaleTraitsT<SourceValueT>;
	using DestTraitsT = ScaleTraitsT<DestValueT>;

	for (std::size_t DestY = 0; DestY != SourceHeight; ++DestY)
	{
		for (std::size_t DestX = 0; DestX != DestWidth; ++DestX)
		{
			auto TapList = TapLists[DestX];
			for (std::size_t C = 0; C != Channels; ++C)
			{
				float DestChannel = 0.0f;
				std::size_t First = TapList.First;
				for (std::size_t I = 0; I != NumTaps; ++I)
				{
					std::size_t Current = First + I;
					float Weight = TapList.Weights[I];
					SourceValueT X = Source[DestY * SourceWidth * Channels + Current * Channels + C];
					DestChannel += SourceTraitsT::convertFrom(X) * Weight;
				}

				DestValueT X = DestTraitsT::convertTo(DestChannel);;
				Dest[DestX * SourceHeight * Channels + DestY * Channels + C] = X;
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
	std::unique_ptr<float[]> HorizData{new float[SourceHeight * DestWidth * Channels]};
	std::unique_ptr<TapListT<NumTaps>[]> HorizSamples{new TapListT<NumTaps>[DestWidth]};
	std::unique_ptr<TapListT<NumTaps>[]> VertSamples{new TapListT<NumTaps>[DestHeight]};

	generateTapLists(SourceWidth, DestWidth, HorizSamples.get(), Filter);
	generateTapLists(SourceHeight, DestHeight, VertSamples.get(), Filter);
	scaleAxis(Source, SourceWidth, SourceHeight, HorizData.get(), DestWidth, Channels, HorizSamples.get());
	scaleAxis(HorizData.get(), SourceHeight, DestWidth, Dest, DestHeight, Channels, VertSamples.get());
}

}
}
