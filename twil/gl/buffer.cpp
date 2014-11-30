#include "buffer.hpp"

#include "context.hpp"

namespace twil {
namespace gl {

Buffer::Buffer()
{
	glGenBuffers(1, &id_);
}

Buffer::~Buffer() noexcept
{
	glDeleteBuffers(1, &id_);
}

Buffer::operator GLuint() const
{
	return id_;
}

}
}
