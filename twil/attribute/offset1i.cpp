#include "offset1i.hpp"

namespace twil {
namespace attribute {

void Offset1I::Setup(GLuint index, GLsizei stride, const GLvoid * offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, 1, GL_UNSIGNED_INT, stride, offset);
}

}
}
