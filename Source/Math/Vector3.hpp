#pragma once

#include "Math/Vector2.hpp"

#include <cmath>

namespace Twil {
namespace Math {

struct Vector3 {
	float X;
	float Y;
	float Z;

	Vector3() = default;
	Vector3(float);
	Vector3(float, float, float);

	static Math::Vector3 UnitX();
	static Math::Vector3 UnitY();
	static Math::Vector3 UnitZ();
	static Math::Vector3 Zero();
	static Math::Vector3 One();
};

Math::Vector3 operator+(Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 operator-(Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 operator*(Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 operator/(Math::Vector3 const &, Math::Vector3 const &);
bool operator==(Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 operator-(Math::Vector3 const &);
float dot(Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 cross(Math::Vector3 const &, Math::Vector3 const &);
float det(Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &);
float getLengthSquared(Math::Vector3 const &);
float getDistanceSquared(Math::Vector3 const &, Math::Vector3 const &);
float getSideOf(Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &);
float getLength(Math::Vector3 const &);
float getDistance(Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 getNormalized(Math::Vector3 const &);
Math::Vector3 getScaled(Math::Vector3 &, float);
Math::Vector3 getNormal(Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 findClosestPointOnLine(Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &);
Math::Vector3 findClosestPointOnSegment(Math::Vector3 const &, Math::Vector3 const &, Math::Vector3 const &);
void operator+=(Math::Vector3 &, Math::Vector3 const &);
void operator-=(Math::Vector3 &, Math::Vector3 const &);
void operator*=(Math::Vector3 &, Math::Vector3 const &);
void operator/=(Math::Vector3 &, Math::Vector3 const &);
void normalize(Math::Vector3 &);
void scale(Math::Vector3 &, float);

}
}
