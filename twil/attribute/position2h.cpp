#include "position2h.hpp"

namespace twil {
namespace attribute {

void Position2H::Setup(GLuint index, GLsizei stride, const GLvoid * offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, 2, GL_SHORT, stride, offset);
}

}
}
