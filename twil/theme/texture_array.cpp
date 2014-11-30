#include "texture_array.hpp"

#include "gl/context.hpp"

namespace twil {
namespace theme {

TextureArray::TextureArray(std::uint32_t format) :
	format_{format}
{}

gl::Texture & TextureArray::GetTexture()
{
	return texture_;
}

void TextureArray::Update()
{
	if (bytes_.size() == size_) return;

	if (capacity_ != bytes_.capacity())
	{
		// Resize and upload all data
		glBindTexture(GL_TEXTURE_BUFFER, texture_);
		glBindBuffer(GL_TEXTURE_BUFFER, buffer_);
		glBufferData(GL_TEXTURE_BUFFER, bytes_.capacity(), nullptr, GL_DYNAMIC_DRAW);
		auto flags = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		auto buffer_pointer = glMapBufferRange(GL_TEXTURE_BUFFER, 0, bytes_.size(), flags);
		auto data_pointer = static_cast<std::uint8_t *>(buffer_pointer);
		std::copy(bytes_.begin(), bytes_.end(), data_pointer);
		glUnmapBuffer(GL_TEXTURE_BUFFER);
		glTexBuffer(GL_TEXTURE_BUFFER, format_, buffer_);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}
	else
	{
		// Upload only new data
		glBindBuffer(GL_TEXTURE_BUFFER, buffer_);
		auto flags = GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
		auto buffer_pointer = glMapBufferRange(GL_TEXTURE_BUFFER, size_, bytes_.size() - size_, flags);
		auto data_pointer = static_cast<std::uint8_t *>(buffer_pointer);
		std::copy(bytes_.begin() + size_, bytes_.end(), data_pointer);
		glUnmapBuffer(GL_TEXTURE_BUFFER);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	capacity_ = bytes_.capacity();
	size_ = bytes_.size();
}

}
}
