#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Texcoord2h {
	GLushort S;
	GLushort T;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
