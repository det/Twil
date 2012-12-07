#include "Math/BarycentricInterpolator.hpp"

namespace Twil {
namespace Math {

BarycentricInterpolator::BarycentricInterpolator(Math::Vector2 const & A, Math::Vector2 const & B, Math::Vector2 const & C) :
	mA{A},
	mB{B},
	mC{C},
	mDet{det(mB - mA, mC - mA)}
{
}

Vector3 BarycentricInterpolator::interpolate(Math::Vector2 const & Point)
{
	auto DetA = det(mB - Point, mC - Point);
	auto DetB = det(mC - Point, mA - Point);
	auto DetC = det(mA - Point, mB - Point);
	return Vector3{DetA, DetB, DetC} / mDet;
}

}
}
