#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

/// \brief Container for an OpenGL buffer.
class BufferT
{
	private:
	GLuint mId;

	// Non copyable
	BufferT(BufferT &) = delete;
	BufferT & operator=(BufferT &) = delete;

	public:
	BufferT();
	~BufferT();

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
