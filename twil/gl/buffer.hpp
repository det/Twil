#pragma once

#include "buffer.hxx"

#include "context.hpp"

namespace twil {
namespace gl {

/// \brief Container for an OpenGL buffer.
class Buffer
{
	Buffer(Buffer const &) = delete;
	Buffer & operator =(Buffer const &) = delete;

private:
	GLuint id_;

public:
	Buffer();
	~Buffer() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
