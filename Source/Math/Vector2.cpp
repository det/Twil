#include "Math/Vector2.hpp"

namespace Twil {
namespace Math {

Vector2::Vector2(float F) :
	X{F},
	Y{F}
{}

Vector2::Vector2(float pX, float pY) :
	X{pX},
	Y{pY}
{}

Math::Vector2 Vector2::UnitX() { return {1, 0}; }
Math::Vector2 Vector2::UnitY() { return {0, 1}; }
Math::Vector2 Vector2::Zero() { return {0, 0}; }
Math::Vector2 Vector2::One() { return {1, 1}; }

Vector2 operator+(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return {
		A.X + B.X,
		A.Y + B.Y
	};
}

Math::Vector2 operator-(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return {
		A.X - B.X,
		A.Y - B.Y
	};
}

Math::Vector2 operator*(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return {
		A.X * B.X,
		A.Y * B.Y
	};
}

Math::Vector2 operator/(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return {
		A.X / B.X,
		A.Y / B.Y
	};
}

bool operator==(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return {
		A.X == B.X &&
		A.Y == B.Y
	};
}

Math::Vector2 operator-(Math::Vector2 const & A)
{
	return {
		-A.X,
		-A.Y
	};
}

float dot(Math::Vector2 const & a, Math::Vector2 const & B)
{
	return {
		a.X * B.X +
		a.Y * B.Y
	};
}

Math::Vector2 cross(Math::Vector2 A)
{
	return {
		 A.Y,
		-A.X
	};
}

float det(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return dot(A, cross(B));
}

float getLengthSquared(Math::Vector2 const & A)
{
	return dot(A, A);
}

float getDistanceSquared(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return getLengthSquared(B - A);
}

float getSideOf(Math::Vector2 const & A, Math::Vector2 const & B, Math::Vector2 const & P)
{
	return det(P - A, B - A);
}

float getLength(Math::Vector2 const & A)
{
	return std::sqrt(getLengthSquared(A));
}

float getDistance(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return std::sqrt(getDistanceSquared(A, B));
}

Math::Vector2 getNormalized(Math::Vector2 const & A)
{
	return A / getLength(A);
}

Math::Vector2 getScaled(Math::Vector2 & A, float Length2) //XXX
{
	return Length2 / getLength(A) * A;
}

Math::Vector2 getNormal(Math::Vector2 const & A, Math::Vector2 const & B)
{
	return getNormalized(cross(B - A));
}

Math::Vector2 findClosestPointOnLine(Math::Vector2 const & A, Math::Vector2 const & B, Math::Vector2 const & P)
{
	auto AP = P - A;
	auto AB = B - A;
	auto AB2 = dot(AB, AB);
	auto APAB = dot(AP, AB);
	auto T = APAB / AB2;
	return A + AB * T;
}

Math::Vector2 findClosestPointOnSegment(Math::Vector2 const & A, Math::Vector2 const & B, Math::Vector2 const & P)
{
	auto AP = P - A;
	auto AB = B - A;
	auto AB2 = dot(AB, AB);
	auto APAB = dot(AP, AB);
	auto T = APAB / AB2;
	if (T < 0) T = 0;
	else if (T > 1) T = 1;
	return A + AB * T;
}

void operator+=(Math::Vector2 & A, Math::Vector2 const & B)
{
	A = A + B;
}

void operator-=(Math::Vector2 & A, Math::Vector2 const & B)
{
	A = A - B;
}

void operator*=(Math::Vector2 & A, Math::Vector2 const & B)
{
	A = A * B;
}

void operator/=(Math::Vector2 & A, Math::Vector2 const & B)
{
	A = A / B;
}

void normalize(Vector2 & A)
{
	A = getNormalized(A);
}

void scale(Vector2 & A, float Length)
{
	A = getScaled(A, Length);
}

}
}


