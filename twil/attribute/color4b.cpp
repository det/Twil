#include "color4b.hpp"

namespace twil {
namespace attribute {

void Color4B::Setup(GLuint index, GLsizei stride, const GLvoid * offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_UNSIGNED_BYTE, true, stride, offset);
}

Color4B Mix(Color4B const & a, Color4B const & b, GLushort weight1)
{
	GLushort weight2 = 65535 - weight1;

	GLubyte red = (a.red * weight1 + b.red * weight2) / 65535;
	GLubyte green = (a.green * weight1 + b.green * weight2) / 65535;
	GLubyte blue = (a.blue * weight1 + b.blue * weight2) / 65535;
	GLubyte alpha = (a.alpha * weight1 + b.alpha * weight2) / 65535;

	return {red, green, blue, alpha};
}

}
}
