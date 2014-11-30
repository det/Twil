#pragma once

#include "color4b.hxx"

#include "gl/context.hpp"

namespace twil {
namespace attribute {

struct Color4B
{
	GLubyte red;
	GLubyte green;
	GLubyte blue;
	GLubyte alpha;

	static void Setup(GLuint, GLsizei, GLvoid const *);
};

Color4B Mix(Color4B const &, Color4B const &, GLushort);

}
}
