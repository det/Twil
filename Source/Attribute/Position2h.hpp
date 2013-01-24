#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Position2hT
{
	GLshort X;
	GLshort Y;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
