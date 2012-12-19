#pragma once

#include "Gl/Buffer.hpp"
#include "Gl/Texture.hpp"

#include <vector>

namespace Twil {
namespace Gl {

class TextureArray
{
	private:
	Gl::Buffer mBuffer;
	Gl::Texture mTexture;

	std::vector<GLubyte> mBytes;
	std::size_t mSize = 0;
	std::size_t mCapacity = 0;

	public:
	operator GLuint();

	void upload();

	template<typename T>
	std::size_t add(T First, T Last)
	{
		auto Index = mBytes.size();
		mBytes.insert(end(mBytes), First, Last);
		return Index;
	}

	template<typename T>
	std::size_t add(std::pair<T, T> Pair)
	{
		return add(Pair.first, Pair.second);
	}
};

}
}
