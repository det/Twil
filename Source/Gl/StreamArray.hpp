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
	StreamArray();
	operator GLuint();

	void add(std::vector<T> const &);
	void upload();
	void clear();
	std::size_t getSize();
};

template<typename T>
StreamArray<T>::StreamArray()
{
	glBindVertexArray(mArray);
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
	T::setup();
	glBindVertexArray(0);
}

template<typename T>
StreamArray<T>::operator GLuint()
{
	return mArray;
}

template<typename T>
void StreamArray<T>::add(std::vector<T> const & Vertices)
{
	mPointers.push_back(&Vertices);
	mSize += Vertices.size();
}

template<typename T>
void StreamArray<T>::upload()
{
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

template<typename T>
void StreamArray<T>::clear()
{
	mSize = 0;
	mPointers.clear();
}

template<typename T>
std::size_t StreamArray<T>::getSize()
{
	return mSize;
}

}
}
