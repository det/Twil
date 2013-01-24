#pragma once

#include "Context.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"

#include <vector>

namespace Twil {
namespace Gl {

/// \brief Container for a dynamically growing OpenGL buffer for streaming data into.
///
/// \param T The vertex type.
template<typename T>
class StreamArrayT
{
	private:
	BufferT mBuffer;
	VertexArrayT mArray;
	std::vector<std::vector<T> const *> mPointers;
	std::size_t mCapacity = 0;
	std::size_t mSize = 0;

	// Non copyable
	StreamArrayT(StreamArrayT &) = delete;
	StreamArrayT & operator=(StreamArrayT &) = delete;

	public:
	StreamArrayT()
	{
		glBindVertexArray(mArray);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
		T::setup();
		glBindVertexArray(0);
	}

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint()
	{
		return mArray;
	}

	/// \brief Queue a vector of vertices for upload.
	///
	/// \param Vertices A vector of vertices to be copied whe upload() is called.
	void queue(std::vector<T> const & Vertices)
	{
		mPointers.push_back(&Vertices);
		mSize += Vertices.size();
	}

	/// \brief Grow the array if needed and stream all the queued vertices to OpenGL.
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
		auto Flags = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		auto BufferPointer = glMapBufferRange(GL_ARRAY_BUFFER, 0, mSize * sizeof(T), Flags);
		auto VertexPointer = static_cast<T *>(BufferPointer);
		for (auto & Pointer : mPointers) {
			auto & Vector = *Pointer;
			VertexPointer = std::copy(begin(Vector), end(Vector), VertexPointer);
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/// \brief Clear the queue.
	void clear()
	{
		mSize = 0;
		mPointers.clear();
	}

	/// \returns The number of vertices in the queue.
	std::size_t getSize() const
	{
		return mSize;
	}
};

}
}
