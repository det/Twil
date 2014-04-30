#pragma once

#include "Texcoord2hFwd.hpp"

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
