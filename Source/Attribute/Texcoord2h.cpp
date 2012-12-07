#include "Attribute/Texcoord2h.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Texcoord2h::setup(GLuint Index, GLsizei Stride, const GLvoid * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 2, GL_UNSIGNED_SHORT, true, Stride, Offset);
}

}
}
