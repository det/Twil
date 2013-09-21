#pragma once

#include "Gl/Buffer.hpp"
#include "Gl/Texture.hpp"

#include <vector>

namespace Twil {
namespace Theme {

/// \brief Container for a dynamicly growing OpenGL buffer texture.
class TextureArrayT
{
	TextureArrayT(TextureArrayT const &) = delete;
	TextureArrayT & operator =(TextureArrayT const &) = delete;

private:
	Gl::BufferT mBuffer;
	Gl::TextureT mTexture;

	std::vector<GLubyte> mBytes;
	std::size_t mSize = 0;
	std::size_t mCapacity = 0;
	GLenum mFormat;

public:
	TextureArrayT(GLenum);

	/// \returns The Texture.
	Gl::TextureT & getTexture();

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
	void update();
};

}
}
