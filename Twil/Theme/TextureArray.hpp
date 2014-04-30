#pragma once

#include "TextureArrayFwd.hpp"

#include "Gl/Buffer.hpp"
#include "Gl/Texture.hpp"

#include <cstdint>
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

	std::vector<std::uint8_t> mBytes;
	std::size_t mSize = 0;
	std::size_t mCapacity = 0;
	std::uint32_t mFormat;

public:
	TextureArrayT(std::uint32_t);

	/// \returns The Texture.
	Gl::TextureT & getTexture();

	std::pair<std::uint8_t *, std::size_t> allocate(std::size_t Bytes)
	{
		auto Size = mBytes.size();
		mBytes.resize(Size + Bytes);
		return {mBytes.data() + Size, Size};
	}

	/// \brief Copies bytes from a pair of iterators into the local buffer.
	/// \returns The begin index for the range.
	template<typename T>
	std::size_t append(T First, T Last)
	{
		auto Index = mBytes.size();

		// Work around libstdc++ bug #61086
		if (mBytes.empty())
		{
			mBytes.push_back(*First);
			++First;
		}

		mBytes.insert(mBytes.end(), First, Last);
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
