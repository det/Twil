#include "Position2h.hpp"

namespace Twil {
namespace Attribute {

void Position2hT::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribIPointer(Index, 2, GL_SHORT, Stride, Offset);
}

}
}
