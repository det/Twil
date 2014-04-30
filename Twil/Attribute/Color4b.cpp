#include "Color4b.hpp"

namespace Twil {
namespace Attribute {

void Color4bT::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 4, GL_UNSIGNED_BYTE, true, Stride, Offset);
}

Color4bT mix(Color4bT const & A, Color4bT const & B, GLushort Weight1)
{
	GLushort Weight2 = 65535 - Weight1;

	GLubyte Red = (A.Red * Weight1 + B.Red * Weight2) / 65535;
	GLubyte Green = (A.Green * Weight1 + B.Green * Weight2) / 65535;
	GLubyte Blue = (A.Blue * Weight1 + B.Blue * Weight2) / 65535;
	GLubyte Alpha = (A.Alpha * Weight1 + B.Alpha * Weight2) / 65535;

	return {Red, Green, Blue, Alpha};
}

}
}
