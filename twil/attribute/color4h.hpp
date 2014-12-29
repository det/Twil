#pragma once

#include "color4h.hxx"

#include "gl/context.hpp"

namespace twil {
namespace attribute {

struct Color4H
{
	GLushort red;
	GLushort green;
	GLushort blue;
	GLushort alpha;

	static void Setup(GLuint, GLsizei, GLvoid const *);
};

Color4H Mix(Color4H const & a, Color4H const & b, GLushort weight1);

}
}
