#include "Math/Matrix2.hpp"

namespace Twil {
namespace Math {

Matrix2::Matrix2(Math::Vector2 const & pX, Math::Vector2 const & pY) :
	X{pX},
	Y{pY}
{}

Math::Matrix2 Matrix2::Identity()
{
	return {
		Math::Vector2::UnitX(),
		Math::Vector2::UnitY()
	};
}

Math::Matrix2 Matrix2::Translation(float X)
{
	return {
		{1, X},
		{0, 1},
	};
}

Math::Matrix2 Matrix2::Scaling(float X, float Y)
{
	return {
		{X, 0},
		{0, Y},
	};
}

Math::Matrix2 Matrix2::RotationZ(float Radians)
{
	auto Cos = std::cos(Radians);
	auto Sin = std::sin(Radians);

	return {
		{Cos, -Sin},
		{Sin, Cos}
	};
}

float det(Math::Matrix2 const & M)
{
	return det(M.X, M.Y);
}

Math::Vector2 operator*(Math::Matrix2 const & M, Math::Vector2 const & V)
{
	return {
		M.X * V.X +
		M.Y * V.Y
	};
}

Math::Vector2 operator*(Math::Vector2 const & V, Math::Matrix2 const & M)
{
	return {
		dot(V, M.X),
		dot(V, M.Y)
	};
}

Math::Matrix2 getTransposed(Math::Matrix2 const & M)
{
	return {
		{M.X.X, M.Y.X},
		{M.X.Y, M.Y.Y}
	};
}

void operator*=(Math::Vector2 & V, Math::Matrix2 const & M)
{
	V = V * M;
}

Math::Matrix2 operator*(Math::Matrix2 const & A, Math::Matrix2 const & B)
{
	return {
		A * B.X,
		A * B.Y
	};
}

}
}
