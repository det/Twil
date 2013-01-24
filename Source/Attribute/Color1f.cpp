#include "Color1f.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Color1fT::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 1, GL_FLOAT, false, Stride, Offset);
}

}
}
