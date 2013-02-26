#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Position2fT
{
	GLfloat X;
	GLfloat Y;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
