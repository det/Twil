#include "color4h.hpp"

namespace twil {
namespace attribute {

void Color4H::Setup(GLuint index, GLsizei stride, const GLvoid * offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_UNSIGNED_SHORT, true, stride, offset);
}

Color4H Mix(Color4H const & a, Color4H const & b, GLushort weight1)
{
	GLushort weight2 = 65535 - weight1;

	GLushort red = (a.red * weight1 + b.red * weight2) / 65535;
	GLushort green = (a.green * weight1 + b.green * weight2) / 65535;
	GLushort blue = (a.blue * weight1 + b.blue * weight2) / 65535;
	GLushort alpha = (a.alpha * weight1 + b.alpha * weight2) / 65535;

	return {red, green, blue, alpha};
}

}
}
