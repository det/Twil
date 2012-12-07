#include "Math/Matrix3.hpp"

namespace Twil {
namespace Math {

Matrix3::Matrix3(Math::Vector3 const & pX, Math::Vector3 const & pY, Math::Vector3 const & pZ) :
	X{pX},
	Y{pY},
	Z{pZ}
{}

Math::Matrix3 Matrix3::Identity()
{
	return {
		Math::Vector3::UnitX(),
		Math::Vector3::UnitY(),
		Math::Vector3::UnitZ()
	};
}

Math::Matrix3 Matrix3::Ortho(float Width, float Height)
{
	return {
		{2 / Width, 0, -1},
		{0, 2 / Height, -1},
		{0, 0, 1}
	};
}

Math::Matrix3 Matrix3::Translation(float X, float Y)
{
	return {
		{1, 0, X},
		{0, 1, Y},
		{0, 0, 1},
	};
}

Math::Matrix3 Matrix3::Scaling(float X, float Y, float Z)
{
	return {
		{X, 0, 0},
		{0, Y, 0},
		{0, 0, Z},
	};
}

Math::Matrix3 Matrix3::RotationX(float Radians)
{
	auto cos = std::cos(Radians);
	auto sin = std::sin(Radians);

	return {
		{1, 0, 0},
		{0, cos, -sin},
		{0, sin, cos},
	};
}

Math::Matrix3 Matrix3::RotationY(float Radians)
{
	auto Cos = std::cos(Radians);
	auto Sin = std::sin(Radians);

	return {
		{Cos, 0, Sin},
		{0, 1, 0},
		{-Sin, 0, Cos},
	};
}

Math::Matrix3 Matrix3::RotationZ(float Radians)
{
	auto Cos = std::cos(Radians);
	auto Sin = std::sin(Radians);

	return {
		{Cos, -Sin, 0},
		{Sin, Cos, 0},
		{0, 0, 1},
	};
}

float det(Math::Matrix3 const & M)
{
	return det(M.X, M.Y, M.Z);
}

Math::Vector3 operator*(Math::Matrix3 const & M, Math::Vector3 const & V)
{
	return {
		M.X * V.X +
		M.Y * V.Y +
		M.Z * V.Z
	};
}

Math::Vector3 operator*(Math::Vector3 const & V, Math::Matrix3 const & M)
{
	return {
		dot(V, M.X),
		dot(V, M.Y),
		dot(V, M.Z)
	};
}

Math::Matrix3 getTransposed(Math::Matrix3 const & M)
{
	return {
		{M.X.X, M.Y.X, M.Z.X},
		{M.X.Y, M.Y.Y, M.Z.Y},
		{M.X.Z, M.Y.Z, M.Z.Z}
	};
}

Math::Matrix3 operator*(Math::Matrix3 const & A, Math::Matrix3 const & B)
{
	return {
		A * B.X,
		A * B.Y,
		A * B.Z
	};
}

void operator*=(Math::Matrix3 & A, Math::Matrix3 const & B)
{
	A = A * B;
}

void operator*=(Math::Vector3 & V, Math::Matrix3 const & M)
{
	V = V * M;
}

}
}
