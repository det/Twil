#pragma once

#include "Math/Vector2.hpp"

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Position2h
{
	GLshort X;
	GLshort Y;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
