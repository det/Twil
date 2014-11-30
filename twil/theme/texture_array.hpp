#pragma once

#include "texture_array.hxx"

#include "gl/buffer.hpp"
#include "gl/texture.hpp"

#include <cstdint>
#include <vector>

namespace twil {
namespace theme {

/// \brief Container for a dynamicly growing OpenGL buffer texture.
class TextureArray
{
	TextureArray(TextureArray const &) = delete;
	TextureArray & operator =(TextureArray const &) = delete;

private:
	gl::Buffer buffer_;
	gl::Texture texture_;

	std::vector<std::uint8_t> bytes_;
	std::size_t size_ = 0;
	std::size_t capacity_ = 0;
	std::uint32_t format_;

public:
	TextureArray(std::uint32_t);

	/// \returns The Texture.
	gl::Texture & GetTexture();

	std::pair<std::uint8_t *, std::size_t> Allocate(std::size_t bytes)
	{
		auto size = bytes_.size();
		bytes_.resize(size + bytes);
		return {bytes_.data() + size, size};
	}

	/// \brief Copies bytes from a pair of iterators into the local buffer.
	/// \returns The begin index for the range.
	template<typename T>
	std::size_t Append(T first, T last)
	{
		auto index = bytes_.size();

		// Work around libstdc++ bug #61086
		if (bytes_.empty())
		{
			bytes_.push_back(*first);
			++first;
		}

		bytes_.insert(bytes_.end(), first, last);
		return index;
	}

	/// \brief Copies bytes from a pair of iterators into the local buffer.
	/// \returns The begin index for the range.
	template<typename T>
	std::size_t Append(std::pair<T, T> pair)
	{
		return Append(pair.first, pair.second);
	}

	/// \brief Syncs the local buffer with OpenGL.
	void Update();
};

}
}
