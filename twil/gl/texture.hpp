#pragma once

#include "texture.hxx"

#include "context.hpp"

namespace twil {
namespace gl {

/// \brief Container for an OpenGL texture.
class Texture
{
	Texture(Texture const &) = delete;
	Texture & operator =(Texture const &) = delete;

private:
	GLuint id_;

public:
	Texture();
	~Texture() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
