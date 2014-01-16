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
	std::uint32_t mId;

public:
	VertexArrayT();
	~VertexArrayT() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator std::uint32_t() const;
};

}
}
