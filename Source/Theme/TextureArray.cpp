#include "TextureArray.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Theme {

TextureArrayT::TextureArrayT(GLenum Format) :
	mFormat{Format}
{}

Gl::TextureT & TextureArrayT::getTexture()
{
	return mTexture;
}

void TextureArrayT::update()
{
	if (mBytes.size() == mSize) return;

	if (mCapacity != mBytes.capacity()) {
		// Resize and upload all data
		glBindTexture(GL_TEXTURE_BUFFER, mTexture);
		glBindBuffer(GL_TEXTURE_BUFFER, mBuffer);
		glBufferData(GL_TEXTURE_BUFFER, mBytes.capacity(), nullptr, GL_DYNAMIC_DRAW);
		auto Flags = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		auto BufferPointer = glMapBufferRange(GL_TEXTURE_BUFFER, 0, mBytes.size(), Flags);
		auto DataPointer = static_cast<GLubyte *>(BufferPointer);
		std::copy(mBytes.begin(), mBytes.end(), DataPointer);
		glUnmapBuffer(GL_TEXTURE_BUFFER);
		glTexBuffer(GL_TEXTURE_BUFFER, mFormat, mBuffer);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}
	else {
		// Upload only new data
		glBindBuffer(GL_TEXTURE_BUFFER, mBuffer);
		auto Flags = GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
		auto BufferPointer = glMapBufferRange(GL_TEXTURE_BUFFER, mSize, mBytes.size() - mSize, Flags);
		auto DataPointer = static_cast<GLubyte *>(BufferPointer);
		std::copy(mBytes.begin() + mSize, mBytes.end(), DataPointer);
		glUnmapBuffer(GL_TEXTURE_BUFFER);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	mCapacity = mBytes.capacity();
	mSize = mBytes.size();
}

}
}
