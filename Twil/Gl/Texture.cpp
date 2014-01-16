#include "Texture.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

TextureT::TextureT()
{
	glGenTextures(1, &mId);
}

TextureT::~TextureT() noexcept
{
	glDeleteTextures(1, &mId);
}

TextureT::operator std::uint32_t() const
{
	return mId;
}

}
}
