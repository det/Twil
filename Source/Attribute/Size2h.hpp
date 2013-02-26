#pragma once

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Size2hT
{
	GLushort Width;
	GLushort Height;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
