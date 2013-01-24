#include "VertexArray.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

VertexArrayT::VertexArrayT()
{
	glGenVertexArrays(1, &mId);
}

VertexArrayT::~VertexArrayT()
{
	glDeleteVertexArrays(1, &mId);
}

VertexArrayT::operator GLuint() const
{
	return mId;
}

}
}
