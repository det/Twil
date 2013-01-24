#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

/// \brief Container for an OpenGL vertex array.
class VertexArrayT
{
	private:
	GLuint mId;

	// Non copyable
	VertexArrayT(VertexArrayT &) = delete;
	VertexArrayT & operator=(VertexArrayT &) = delete;

	public:
	VertexArrayT();
	~VertexArrayT();

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
