#include "Math/Vector4.hpp"

namespace Twil {
namespace Math {

Vector4::Vector4(float F) :
	X{F},
	Y{F},
	Z{F},
	W{F}
{}

Vector4::Vector4(float pX, float pY, float pZ, float pW) :
	X{pX},
	Y{pY},
	Z{pZ},
	W{pW}
{}

Math::Vector4 Vector4::UnitX() { return {1, 0, 0, 0}; }
Math::Vector4 Vector4::UnitY() { return {0, 1, 0, 0}; }
Math::Vector4 Vector4::UnitZ() { return {0, 0, 1, 0}; }
Math::Vector4 Vector4::UnitW() { return {0, 0, 0, 1}; }
Math::Vector4 Vector4::Zero() { return {0, 0, 0, 0}; }
Math::Vector4 Vector4::One() { return {1, 1, 1, 1}; }

Math::Vector4 operator+(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return {
		A.X + B.X,
		A.Y + B.Y,
		A.Z + B.Z,
		A.W + B.W
	};
}

Math::Vector4 operator-(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return {
		A.X - B.X,
		A.Y - B.Y,
		A.Z - B.Z,
		A.W - B.W
	};
}

Math::Vector4 operator*(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return {
		A.X * B.X,
		A.Y * B.Y,
		A.Z * B.Z,
		A.W * B.W
	};
}

Math::Vector4 operator/(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return {
		A.X / B.X,
		A.Y / B.Y,
		A.Z / B.Z,
		A.W / B.W
	};
}

bool operator==(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return {
		A.X == B.X &&
		A.Y == B.Y &&
		A.Z == B.Z &&
		A.W == B.W
	};
}

Math::Vector4 operator-(Math::Vector4 const & A)
{
	return {
		-A.X,
		-A.Y,
		-A.Z,
		-A.W
	};
}

float dot(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return {
		A.X * B.X +
		A.Y * B.Y +
		A.Z * B.Z +
		A.W * B.W
	};
}

Math::Vector4 cross(Math::Vector4 const & A, Math::Vector4 const & B, Math::Vector4 const & C)
{
	return {
		 det({C.W, C.Z, C.Y}, {B.W, B.Z, B.Y}, {A.W, A.Z, A.Y}),
		-det({C.W, C.Z, C.X}, {B.W, B.Z, B.X}, {A.W, A.Z, A.X}),
		 det({C.W, C.Y, C.X}, {B.W, B.Y, B.X}, {A.W, A.Y, A.X}),
		-det({C.Z, C.Y, C.X}, {B.Z, B.Y, B.X}, {A.Z, A.Y, A.X})
	};
}

float det(Math::Vector4 const & A, Math::Vector4 const & B, Math::Vector4 const & C, Math::Vector4 const & D)
{
	return dot(A, cross(B, C, D));
}

float getLengthSquared(Math::Vector4 const & A)
{
	return dot(A, A);
}

float getDistanceSquared(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return getLengthSquared(B - A);
}

float getSideOf(Math::Vector4 const & A, Math::Vector4 const & B, Math::Vector4 const & C, Math::Vector4 const & D, Math::Vector4 const & P)
{
	return det(P - A, B - A, C - A, D - A);
}

float getLength(Math::Vector4 const & A)
{
	return std::sqrt(getLengthSquared(A));
}

float getDistance(Math::Vector4 const & A, Math::Vector4 const & B)
{
	return std::sqrt(getDistanceSquared(A, B));
}

Math::Vector4 getNormalized(Math::Vector4 const & A)
{
	return A / getLength(A);
}

Math::Vector4 getScaled(Math::Vector4 & A, float Length2) //XXX
{
	return Length2 / getLength(A) * A;
}

Math::Vector4 getNormal(Math::Vector4 const & A, Math::Vector4 const & B, Math::Vector4 const & C, Math::Vector4 const & D)
{
	return getNormalized(cross(B - A, C - A, D - A));
}

Math::Vector4 findClosestPointOnLine(Math::Vector4 const & A, Math::Vector4 const & B, Math::Vector4 const & P)
{
	auto AP = P - A;
	auto AB = B - A;
	auto AB2 = dot(AB, AB);
	auto APAB = dot(AP, AB);
	auto T = APAB / AB2;
	return A + AB * T;
}

Math::Vector4 findClosestPointOnSegment(Math::Vector4 const & A, Math::Vector4 const & B, Math::Vector4 const & P)
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

void operator+=(Math::Vector4 & A, Math::Vector4 const & B)
{
	A = A + B;
}

void operator-=(Math::Vector4 & A, Math::Vector4 const & B)
{
	A = A - B;
}

void operator*=(Math::Vector4 & A, Math::Vector4 const & B)
{
	A = A * B;
}

void operator/=(Math::Vector4 & A, Math::Vector4 const & B)
{
	A = A / B;
}

void normalize(Math::Vector4 & A)
{
	A = getNormalized(A);
}

void scale(Math::Vector4 & A, float Length)
{
	A = getScaled(A, Length);
}

}
}

