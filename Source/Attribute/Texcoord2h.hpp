#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Texcoord2hT
{
	GLushort S;
	GLushort T;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
