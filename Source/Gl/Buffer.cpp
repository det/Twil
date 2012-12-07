#include "Gl/Buffer.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Gl {

Buffer::Buffer()
{
	glGenBuffers(1, &mId);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &mId);
}

Buffer::operator GLuint() const
{
	return mId;
}

}
}
