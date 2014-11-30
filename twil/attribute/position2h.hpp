#pragma once

#include "position2h.hxx"

#include "gl/context.hpp"

namespace twil {
namespace attribute {

struct Position2H
{
	GLshort x;
	GLshort y;

	static void Setup(GLuint, GLsizei, GLvoid const *);
};

}
}
