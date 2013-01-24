#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Color1fT
{
	GLfloat Red;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
