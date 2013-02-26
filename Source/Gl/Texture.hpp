#pragma once

#include "Context.hpp"

namespace Twil {
namespace Gl {

/// \brief Container for an OpenGL texture.
class TextureT
{
	private:
	public:
	GLuint mId;

	// Non copyable
	TextureT(TextureT &) = delete;
	TextureT & operator=(TextureT &) = delete;

	public:
	TextureT();
	~TextureT();

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
