#pragma once

#include "Buffer.hpp"
#include "Texture.hpp"

#include <vector>

namespace Twil {
namespace Gl {

/// \brief Container for a dynamicly growing OpenGL buffer texture.
class TextureArrayT
{
	private:
	BufferT mBuffer;
	TextureT mTexture;

	// Non copyable
	TextureArrayT(TextureArrayT &) = delete;
	TextureArrayT & operator=(TextureArrayT &) = delete;

	std::vector<GLubyte> mBytes;
	std::size_t mSize = 0;
	std::size_t mCapacity = 0;

	public:
	TextureArrayT() = default;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint();

	/// \brief Copies bytes from a pair of iterators into the local buffer.
	/// \returns The begin index for the range.
	template<typename T>
	std::size_t append(T First, T Last)
	{
		auto Index = mBytes.size();
		mBytes.insert(end(mBytes), First, Last);
		return Index;
	}

	/// \brief Copies bytes from a pair of iterators into the local buffer.
	/// \returns The begin index for the range.
	template<typename T>
	std::size_t append(std::pair<T, T> Pair)
	{
		return append(Pair.first, Pair.second);
	}

	/// \brief Syncs the local buffer with OpenGL.
	void upload();
};

}
}
