#include "TextureArray.hpp"

#include "Context.hpp"

namespace Twil {
namespace Gl {

TextureArrayT::operator GLuint()
{
	return mTexture;
}

void TextureArrayT::upload()
{
	if (mBytes.size() == mSize) return;

	if (mCapacity != mBytes.capacity()) {
		// Resize and upload all data
		glBindTexture(GL_TEXTURE_BUFFER, mTexture);
		glBindBuffer(GL_TEXTURE_BUFFER, mBuffer);
		glBufferData(GL_TEXTURE_BUFFER, mBytes.capacity(), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_TEXTURE_BUFFER, 0, mBytes.size(), mBytes.data());
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8, mBuffer);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}
	else {
		// Upload only new data
		glBindBuffer(GL_TEXTURE_BUFFER, mBuffer);
		glBufferSubData(GL_TEXTURE_BUFFER, mSize, mBytes.size() - mSize, mBytes.data() + mSize);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	mCapacity = mBytes.capacity();
	mSize = mBytes.size();
}

}
}
