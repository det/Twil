#include "Attribute/Color4b.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Color4b::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 4, GL_UNSIGNED_BYTE, true, Stride, Offset);
}

Attribute::Color4b mix(Attribute::Color4b const & A, Attribute::Color4b const & B, unsigned ValA, unsigned ValB)
{
	unsigned char Weight2 = (ValB * 255 / ValA * 255) / 255;
	unsigned char Weight1 = 255 - Weight2;

	return {
		GLubyte((A.Red * Weight1 + B.Red * Weight2) / 255),
		GLubyte((A.Green * Weight1 + B.Green * Weight2) / 255),
		GLubyte((A.Blue * Weight1 + B.Blue * Weight2) / 255),
		GLubyte((A.Alpha * Weight1 + B.Alpha * Weight2) / 255)
	};
}

}
}
