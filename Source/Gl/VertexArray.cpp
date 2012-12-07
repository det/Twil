#include "Gl/VertexArray.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Gl {

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mId);
}

VertexArray::operator GLuint() const
{
	return mId;
}

}
}
