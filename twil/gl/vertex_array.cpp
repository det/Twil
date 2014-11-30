#include "vertex_array.hpp"

#include "context.hpp"

namespace twil {
namespace gl {

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() noexcept
{
	glDeleteVertexArrays(1, &id_);
}

VertexArray::operator GLuint() const
{
	return id_;
}

}
}
