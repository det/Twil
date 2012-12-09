#pragma once

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

namespace Twil {
namespace Math {

class BarycentricInterpolator
{
	private:
	Math::Vector2 mA;
	Math::Vector2 mB;
	Math::Vector2 mC;
	float mDet;

	public:
	BarycentricInterpolator(Math::Vector2 const &, Math::Vector2 const &, Math::Vector2 const &);
	Vector3 interpolate(Math::Vector2 const &);
};

}
}
