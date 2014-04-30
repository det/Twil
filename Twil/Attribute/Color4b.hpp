#pragma once

#include "Color4bFwd.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Color4bT
{
	GLubyte Red;
	GLubyte Green;
	GLubyte Blue;
	GLubyte Alpha;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

Color4bT mix(Color4bT const &, Color4bT const &, GLushort);

}
}
