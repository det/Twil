#pragma once

#include "Offset1iFwd.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

struct Offset1iT
{
	GLuint Value;

	static void setup(GLuint, GLsizei, GLvoid const *);
};

}
}
