#pragma once

#include "Math/Vector4.hpp"

namespace Twil {
namespace Math {

struct Matrix4
{
	Math::Vector4 X;
	Math::Vector4 Y;
	Math::Vector4 Z;
	Math::Vector4 W;

	Matrix4() = default;
	Matrix4(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);

	static Math::Matrix4 Identity();
	static Math::Matrix4 Translation(float, float, float);
	static Math::Matrix4 Scaling(float, float, float, float);
	static Math::Matrix4 RotationX(float);
	static Math::Matrix4 RotationY(float);
	static Math::Matrix4 RotationZ(float);
};

float det(Matrix4 const &);
Math::Vector4 operator*(Math::Matrix4 const &, Math::Vector4 const &);
Math::Vector4 operator*(Math::Vector4 const &, Math::Matrix4 const &);
Math::Matrix4 getTransposed(Math::Matrix4 &);
Math::Matrix4 operator*(Math::Matrix4 const &, Math::Matrix4 const &);
void operator*=(Math::Vector4 &, Math::Matrix4 const &);

}
}

