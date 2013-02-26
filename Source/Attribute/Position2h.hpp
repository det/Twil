#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Position2hT
{
	GLshort X;
	GLshort Y;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
