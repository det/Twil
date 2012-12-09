#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Texcoord1f
{
	GLfloat S;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
