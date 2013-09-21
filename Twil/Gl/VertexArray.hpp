#pragma once

#include "Context.hpp"

namespace Twil {
namespace Gl {

/// \brief Container for an OpenGL vertex array.
class VertexArrayT
{
	VertexArrayT(VertexArrayT const &) = delete;
	VertexArrayT & operator =(VertexArrayT const &) = delete;

private:
	GLuint mId;

public:
	VertexArrayT();
	~VertexArrayT();

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
