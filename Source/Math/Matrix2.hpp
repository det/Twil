#pragma once

#include "Math/Vector2.hpp"

namespace Twil {
namespace Math {

struct Matrix2 {
	Math::Vector2 X;
	Math::Vector2 Y;

	Matrix2() = default;
	Matrix2(Math::Vector2 const &, Math::Vector2 const &);

	static Math::Matrix2 Identity();
	static Math::Matrix2 Translation(float);
	static Math::Matrix2 Scaling(float, float);
	static Math::Matrix2 RotationZ(float);
};

float det(Math::Matrix2 const &);
Math::Vector2 operator*(Math::Matrix2 const &, Math::Vector2 const &);
Math::Vector2 operator*(Math::Vector2 const &, Math::Matrix2 const &);
Math::Matrix2 getTransposed(Math::Matrix2 const &);
void operator*=(Math::Vector2 &, Math::Matrix2 const &);
Math::Matrix2 operator*(Math::Matrix2 const &, Math::Matrix2 const &);

}
}
