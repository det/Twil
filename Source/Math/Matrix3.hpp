#pragma once

#include "Math/Vector3.hpp"

namespace Twil {
namespace Math {

struct Matrix3
{
	Math::Vector3 X;
	Math::Vector3 Y;
	Math::Vector3 Z;

	Matrix3() = default;
	Matrix3(Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &);

	static Math::Matrix3 Identity();
	static Math::Matrix3 Ortho(float, float);
	static Math::Matrix3 Translation(float, float);
	static Math::Matrix3 Scaling(float, float, float);
	static Math::Matrix3 RotationX(float);
	static Math::Matrix3 RotationY(float);
	static Math::Matrix3 RotationZ(float);
};

float det(Math::Matrix3 const &);
Math::Vector3 operator*(Math::Matrix3 const &, Math::Vector3 const &);
Math::Vector3 operator*(Math::Vector3 const &, Math::Matrix3 const &);
Math::Matrix3 getTransposed(Math::Matrix3 const &);
Math::Matrix3 operator*(Math::Matrix3 const &, Math::Matrix3 const &);
void operator*=(Math::Matrix3 &, Math::Matrix3 const &);
void operator*=(Math::Vector3 &, Math::Matrix3 const &);

}
}
