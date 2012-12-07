#include "Attribute/Size2h.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Size2h::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribIPointer(Index, 2, GL_UNSIGNED_SHORT, Stride, Offset);
}

}
}
