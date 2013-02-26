#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Color1fT
{
	GLfloat Red;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
