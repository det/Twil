#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Attribute {

struct Color4b {
	GLubyte Red;
	GLubyte Green;
	GLubyte Blue;
	GLubyte Alpha;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

Attribute::Color4b mix(Attribute::Color4b const &, Attribute::Color4b const &, unsigned, unsigned);

}
}
