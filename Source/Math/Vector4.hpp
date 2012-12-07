#pragma once

#include "Math/Vector3.hpp"

namespace Twil {
namespace Math {

struct Vector4 {
	float X;
	float Y;
	float Z;
	float W;

	Vector4() = default;
	Vector4(float);
	Vector4(float, float, float, float);

	static Math::Vector4 UnitX();
	static Math::Vector4 UnitY();
	static Math::Vector4 UnitZ();
	static Math::Vector4 UnitW();
	static Math::Vector4 Zero();
	static Math::Vector4 One();
};

Math::Vector4 operator+(Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 operator-(Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 operator*(Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 operator/(Math::Vector4 const &, Math::Vector4 const &);
bool operator==(Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 operator-(Math::Vector4 const &);
float dot(Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 cross(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);
float det(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);
float getLengthSquared(Math::Vector4 const &);
float getDistanceSquared(Math::Vector4 const &, Math::Vector4 const &);
float getSideOf(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);
float getLength(Math::Vector4 const &);
float getDistance(Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 getNormalized(Math::Vector4 const &);
Math::Vector4 getScaled(Math::Vector4 &, float);
Math::Vector4 getNormal(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 findClosestPointOnLine(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);
Math::Vector4 findClosestPointOnSegment(Math::Vector4 const &, Math::Vector4 const &, Math::Vector4 const &);
void operator+=(Math::Vector4 &, Math::Vector4 const &);
void operator-=(Math::Vector4 &, Math::Vector4 const &);
void operator*=(Math::Vector4 &, Math::Vector4 const &);
void operator/=(Math::Vector4 &, Math::Vector4 const &);
void normalize(Math::Vector4 &);
void scale(Math::Vector4 &, float);

}
}

