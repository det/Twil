#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Size2h
{
	GLushort Width;
	GLushort Height;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
