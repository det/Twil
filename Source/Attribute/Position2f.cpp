#include "Attribute/Position2f.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Position2f::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 2, GL_FLOAT, false, Stride, Offset);
}

}
}
