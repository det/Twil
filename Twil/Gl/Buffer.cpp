#include "Buffer.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

BufferT::BufferT()
{
	glGenBuffers(1, &mId);
}

BufferT::~BufferT()
{
	glDeleteBuffers(1, &mId);
}

BufferT::operator GLuint() const
{
	return mId;
}

}
}
