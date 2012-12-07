#pragma once

#include <cmath>
#include <stdint.h>

namespace Twil {
namespace Math {

struct Vector2 {
	float X;
	float Y;

	Vector2() = default;
	Vector2(float);
	Vector2(float, float);

	static Math::Vector2 UnitX();
	static Math::Vector2 UnitY();
	static Math::Vector2 Zero();
	static Math::Vector2 One();
};

Vector2 operator+(Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 operator-(Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 operator*(Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 operator/(Math::Vector2 const &, Math::Vector2 const &);
bool operator==(Math::Vector2 const &, Math::Vector2 const &);
float dot(Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 cross(Math::Vector2);
float det(Math::Vector2 const &, Math::Vector2 const &);
float getLengthSquared(Math::Vector2 const &);
float getDistanceSquared(Math::Vector2 const &, Math::Vector2 const &);
float getSideOf(Math::Vector2 const &, Math::Vector2 const &, Math::Vector2 const &);
float getLength(Math::Vector2 const &);
float getDistance(Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 getNormalized(Math::Vector2 const &);
Math::Vector2 getScaled(Math::Vector2 &, float);
Math::Vector2 getNormal(Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 findClosestPointOnLine(Math::Vector2 const &, Math::Vector2 const &, Math::Vector2 const &);
Math::Vector2 findClosestPointOnSegment(Math::Vector2 const &, Math::Vector2 const &, Math::Vector2 const &);
void operator+=(Math::Vector2 & a, Math::Vector2 const &);
void operator-=(Math::Vector2 & a, Math::Vector2 const &);
void operator*=(Math::Vector2 & a, Math::Vector2 const &);
void operator/=(Math::Vector2 & a, Math::Vector2 const &);
void normalize(Vector2 &);
void scale(Vector2 &, float);

}
}

