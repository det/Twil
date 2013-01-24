#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Offset1iT
{
	GLuint Value;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
