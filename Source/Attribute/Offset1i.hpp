#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Offset1i
{
	GLuint Value;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
