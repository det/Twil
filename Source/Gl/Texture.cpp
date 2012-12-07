#include "Gl/Texture.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Gl {

Texture::Texture()
{
	glGenTextures(1, &mId);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}

Texture::operator GLuint() const
{
	return mId;
}

}
}
