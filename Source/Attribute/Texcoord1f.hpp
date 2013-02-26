#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Texcoord1fT
{
	GLfloat S;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
