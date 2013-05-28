#include "Offset1i.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Offset1iT::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribIPointer(Index, 1, GL_UNSIGNED_INT, Stride, Offset);
}

}
}
