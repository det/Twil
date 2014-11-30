#include "texcoord2h.hpp"

namespace twil {
namespace attribute {

void Texcoord2H::Setup(GLuint index, GLsizei stride, const GLvoid * offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 2, GL_UNSIGNED_SHORT, true, stride, offset);
}

}
}
