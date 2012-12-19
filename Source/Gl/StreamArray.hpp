#pragma once

#include "Gl/Context.hpp"
#include "Gl/Buffer.hpp"
#include "Gl/VertexArray.hpp"

#include <iostream>
#include <vector>

namespace Twil {
namespace Gl {

template<typename T>
class StreamArray
{
	private:
	Gl::Buffer mBuffer;
	Gl::VertexArray mArray;
	std::vector<std::vector<T> const *> mPointers;
	std::size_t mCapacity = 0;
	std::size_t mSize = 0;

	public:
	StreamArray()
	{
		glBindVertexArray(mArray);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
		T::setup();
		glBindVertexArray(0);
	}

	operator GLuint()
	{
		return mArray;
	}

	void add(std::vector<T> const & Vertices)
	{
		mPointers.push_back(&Vertices);
		mSize += Vertices.size();
	}

	void upload()
	{
		// You cant map a buffer of size 0
		if (mSize == 0) return;

		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		// If the buffer is too small, resize it
		if (mSize > mCapacity) {
			if (mCapacity == 0) mCapacity = 1;
			while (mSize > mCapacity) mCapacity *= 2;
			glBufferData(GL_ARRAY_BUFFER, mCapacity * sizeof(T), nullptr, GL_STREAM_DRAW);
		}

		// Map the buffer and upload vertices
		auto BufferPointer = glMapBufferRange(GL_ARRAY_BUFFER, 0, mSize * sizeof(T), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		auto VertexPointer = static_cast<T *>(BufferPointer);
		for (auto & Pointer : mPointers) {
			auto & Vector = *Pointer;
			VertexPointer = std::copy(begin(Vector), end(Vector), VertexPointer);
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void clear()
	{
		mSize = 0;
		mPointers.clear();
	}

	std::size_t getSize()
	{
		return mSize;
	}
};

}
}
