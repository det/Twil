#include "Attribute/Position2h.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Position2h::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 2, GL_SHORT, false, Stride, Offset);
}

}
}
