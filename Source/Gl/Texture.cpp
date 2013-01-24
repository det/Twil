#include "Texture.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

TextureT::TextureT()
{
	glGenTextures(1, &mId);
}

TextureT::~TextureT()
{
	glDeleteTextures(1, &mId);
}

TextureT::operator GLuint() const
{
	return mId;
}

}
}
