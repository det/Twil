#pragma once

#include "Context.hpp"

namespace Twil {
namespace Gl {

/// \brief Container for an OpenGL texture.
class TextureT
{
	TextureT(TextureT const &) = delete;
	TextureT & operator =(TextureT const &) = delete;

private:
	GLuint mId;

public:
	TextureT();
	~TextureT() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
