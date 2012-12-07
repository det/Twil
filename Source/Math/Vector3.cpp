#include "Math/Vector3.hpp"

namespace Twil {
namespace Math {

Vector3::Vector3(float F) :
	X{F},
	Y{F},
	Z{F}
{}

Vector3::Vector3(float pX, float pY, float pZ) :
	X{pX},
	Y{pY},
	Z{pZ}
{}

Math::Vector3 Vector3::UnitX() { return {1, 0, 0}; }
Math::Vector3 Vector3::UnitY() { return {0, 1, 0}; }
Math::Vector3 Vector3::UnitZ() { return {0, 0, 1}; }
Math::Vector3 Vector3::Zero()  { return {0, 0, 0}; }
Math::Vector3 Vector3::One() { return {1, 1, 1}; }

Math::Vector3 operator+(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		A.X + B.X,
		A.Y + B.Y,
		A.Z + B.Z
	};
}

Math::Vector3 operator-(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		A.X - B.X,
		A.Y - B.Y,
		A.Z - B.Z
	};
}

Math::Vector3 operator*(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		A.X * B.X,
		A.Y * B.Y,
		A.Z * B.Z
	};
}

Math::Vector3 operator/(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		A.X / B.X,
		A.Y / B.Y,
		A.Z / B.Z
	};
}

bool operator==(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		A.X == B.X &&
		A.Y == B.Y &&
		A.Z == B.Z
	};
}

Math::Vector3 operator-(Math::Vector3 const & A)
{
	return {
		-A.X,
		-A.Y,
		-A.Z
	};
}

float dot(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		A.X * B.X +
		A.Y * B.Y +
		A.Z * B.Z
	};
}

Math::Vector3 cross(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return {
		 det({B.Z, B.Y}, {A.Z, A.Y}),
		-det({B.Z, B.X}, {A.Z, A.X}),
		 det({B.Y, B.X}, {A.Y, A.X})
	};
}

float det(Math::Vector3 const & A, Math::Vector3 const & B, Math::Vector3 const & C)
{
	return dot(A, cross(B, C));
}

float getLengthSquared(Math::Vector3 const & A)
{
	return dot(A, A);
}

float getDistanceSquared(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return getLengthSquared(B - A);
}

float getSideOf(Math::Vector3 const & A, Math::Vector3 const & B, Math::Vector3 const & C, Math::Vector3 const & P)
{
	return det(P - A, B - A, C - A);
}

float getLength(Math::Vector3 const & A)
{
	return std::sqrt(getLengthSquared(A));
}

float getDistance(Math::Vector3 const & A, Math::Vector3 const & B)
{
	return std::sqrt(getDistanceSquared(A, B));
}

Math::Vector3 getNormalized(Math::Vector3 const & A)
{
	return A / getLength(A);
}

Math::Vector3 getScaled(Math::Vector3 & A, float Length2) //xxx
{
	return Length2 / getLength(A) * A;
}

Math::Vector3 getNormal(Math::Vector3 const & A, Math::Vector3 const & B, Math::Vector3 const & C)
{
	return getNormalized(cross(B - A, C - A));
}

Math::Vector3 findClosestPointOnLine(Math::Vector3 const & A, Math::Vector3 const & B, Math::Vector3 const & P)
{
	auto AP = P - A;
	auto AB = B - A;
	auto AB2 = dot(AB, AB);
	auto APAB = dot(AP, AB);
	auto T = APAB / AB2;
	return A + AB * T;
}

Math::Vector3 findClosestPointOnSegment(Math::Vector3 const & A, Math::Vector3 const & B, Math::Vector3 const & P)
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

void operator+=(Math::Vector3 & A, Math::Vector3 const & B)
{
	A = A + B;
}

void operator-=(Math::Vector3 & A, Math::Vector3 const & B)
{
	A = A - B;
}

void operator*=(Math::Vector3 & A, Math::Vector3 const & B)
{
	A = A * B;
}

void operator/=(Math::Vector3 & A, Math::Vector3 const & B)
{
	A = A / B;
}

void normalize(Math::Vector3 & A)
{
	A = getNormalized(A);
}

void scale(Math::Vector3 & A, float Length)
{
	A = getScaled(A, Length);
}

}
}
