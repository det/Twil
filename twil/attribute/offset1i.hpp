#pragma once

#include "offset1i.hxx"

#include "gl/context.hpp"

namespace twil {
namespace attribute {

struct Offset1I
{
	GLuint value;

	static void Setup(GLuint, GLsizei, GLvoid const *);
};

}
}
