#pragma once

#include "Context.hpp"

namespace Twil {
namespace Gl {

/// \brief Container for an OpenGL buffer.
class BufferT
{
	BufferT(BufferT const &) = delete;
	BufferT & operator =(BufferT const &) = delete;

private:
	std::uint32_t mId;

public:
	BufferT();
	~BufferT() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator std::uint32_t() const;
};

}
}
