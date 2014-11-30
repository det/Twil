#pragma once

#include "size2h.hxx"

#include "gl/context.hpp"

namespace twil {
namespace attribute {

struct Size2H
{
	GLushort width;
	GLushort height;

	static void Setup(GLuint, GLsizei, GLvoid const *);
};

}
}
