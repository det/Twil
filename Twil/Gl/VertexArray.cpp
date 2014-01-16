#include "VertexArray.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

VertexArrayT::VertexArrayT()
{
	glGenVertexArrays(1, &mId);
}

VertexArrayT::~VertexArrayT() noexcept
{
	glDeleteVertexArrays(1, &mId);
}

VertexArrayT::operator std::uint32_t() const
{
	return mId;
}

}
}
