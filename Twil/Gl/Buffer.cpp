#include "Buffer.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

BufferT::BufferT()
{
	glGenBuffers(1, &mId);
}

BufferT::~BufferT() noexcept
{
	glDeleteBuffers(1, &mId);
}

BufferT::operator std::uint32_t() const
{
	return mId;
}

}
}
