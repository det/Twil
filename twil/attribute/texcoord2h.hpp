#pragma once

#include "texcoord2h.hxx"

#include "gl/context.hpp"

namespace twil {
namespace attribute {

struct Texcoord2H
{
	GLushort s;
	GLushort t;

	static void Setup(GLuint, GLsizei, GLvoid const *);
};

}
}
