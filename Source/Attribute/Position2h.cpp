#include "Position2h.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Position2hT::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribIPointer(Index, 2, GL_SHORT, Stride, Offset);
}

}
}
