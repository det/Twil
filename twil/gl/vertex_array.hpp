#pragma once

#include "vertex_array.hxx"

#include "context.hpp"

namespace twil {
namespace gl {

/// \brief Container for an OpenGL vertex array.
class VertexArray
{
	VertexArray(VertexArray const &) = delete;
	VertexArray & operator =(VertexArray const &) = delete;

private:
	GLuint id_;

public:
	VertexArray();
	~VertexArray() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;
};

}
}
