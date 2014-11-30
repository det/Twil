#include "size2h.hpp"

namespace twil {
namespace attribute {

void Size2H::Setup(GLuint index, GLsizei stride, const GLvoid * offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, 2, GL_UNSIGNED_SHORT, stride, offset);
}

}
}
