#include "texture.hpp"

#include "context.hpp"

namespace twil {
namespace gl {

Texture::Texture()
{
	glGenTextures(1, &id_);
}

Texture::~Texture() noexcept
{
	glDeleteTextures(1, &id_);
}

Texture::operator GLuint() const
{
	return id_;
}

}
}
