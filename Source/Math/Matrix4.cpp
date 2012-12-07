#include "Math/Matrix4.hpp"

namespace Twil {
namespace Math {

Matrix4::Matrix4(Math::Vector4 const & pX, Math::Vector4 const & pY, Math::Vector4 const & pZ, Math::Vector4 const & pW) :
	X{pX},
	Y{pY},
	Z{pZ},
	W{pW}
{}

Math::Matrix4 Matrix4::Identity()
{
	return {
		Vector4::UnitX(),
		Vector4::UnitY(),
		Vector4::UnitZ(),
		Vector4::UnitW()
	};
}

Math::Matrix4 Matrix4::Translation(float X, float Y, float Z)
{
	return {
		{1, 0, 0, X},
		{0, 1, 0, Y},
		{0, 0, 1, Z},
		{0, 0, 0, 1}
	};
}

Math::Matrix4 Matrix4::Scaling(float X, float Y, float Z, float W)
{
	return {
		{X, 0, 0, 0},
		{0, Y, 0, 0},
		{0, 0, Z, 0},
		{0, 0, 0, W}
	};
}

Math::Matrix4 Matrix4::RotationX(float Radians)
{
	auto Cos = std::cos(Radians);
	auto Sin = std::sin(Radians);

	return {
		{1, 0, 0, 0},
		{0, Cos, -Sin, 0},
		{0, Sin, Cos, 0},
		{0, 0, 0, 1}
	};
}

Math::Matrix4 Matrix4::RotationY(float Radians)
{
	auto cos = std::cos(Radians);
	auto sin = std::sin(Radians);

	return {
		{cos, 0, sin, 0},
		{0, 1, 0, 0},
		{-sin, 0, cos, 0},
		{0, 0, 0, 1}
	};
}

Math::Matrix4 Matrix4::RotationZ(float Radians)
{
	auto Cos = std::cos(Radians);
	auto Sin = std::sin(Radians);

	return {
		{Cos, -Sin, 0, 0},
		{Sin, Cos, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
}

float det(Matrix4 const & M)
{
	return det(M.X, M.Y, M.Z, M.W);
}

Math::Vector4 operator*(Math::Matrix4 const & M, Math::Vector4 const & V)
{
	return {
		M.X * V.X +
		M.Y * V.Y +
		M.Z * V.Z +
		M.W * V.W
	};
}

Math::Vector4 operator*(Math::Vector4 const & V, Math::Matrix4 const & M)
{
	return {
		dot(V, M.X),
		dot(V, M.Y),
		dot(V, M.Z),
		dot(V, M.W)
	};
}

Math::Matrix4 getTransposed(Math::Matrix4 & M)
{
	return {
		{M.X.X, M.Y.X, M.Z.X, M.W.X},
		{M.X.Y, M.Y.Y, M.Z.Y, M.W.Y},
		{M.X.Z, M.Y.Z, M.Z.Z, M.W.Z},
		{M.X.W, M.Y.W, M.Z.W, M.W.W}
	};
}

Math::Matrix4 operator*(Math::Matrix4 const & A, Math::Matrix4 const & B)
{
	return {
		A * B.X,
		A * B.Y,
		A * B.Z,
		A * B.W
	};
}

void operator*=(Math::Vector4 & V, Math::Matrix4 const & M)
{
	V = V * M;
}

}
}
