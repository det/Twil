#pragma once

#include "Drawable.hpp"
#include "Gl/Buffer.hpp"
#include "Gl/Context.hpp"
#include "Gl/VertexArray.hpp"

#include <cassert>
#include <vector>

namespace Twil {
namespace Theme {

/// \brief Container for a dynamically growing OpenGL buffer for streaming data into.
///
/// \param T The vertex type.
template<typename T>
class StreamArrayT
{
	private:
	Gl::BufferT mBuffer;
	Gl::VertexArrayT mArray;
	std::size_t mCapacity = 0;
	std::size_t mSize = 0;
	std::vector<DrawableT<T> *> mDrawables;
	bool mNeedsRedraw = false;
	bool mNeedsCompact = false;

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

	/// \brief Add a Drawable to the draw queue.
	void allocate(DrawableT<T> & Drawable, std::size_t Size)
	{
		Drawable.mSize = Size;
		mDrawables.push_back(&Drawable);
		mSize += Drawable.mSize;
	}

	/// \brief Resize the allocation for a Drawable.
	void resize(DrawableT<T> & Drawable, std::size_t Size)
	{
		mSize -= Drawable.mSize;
		mSize += Size;
		Drawable.mSize = Size;
	}

	/// \brief Mark a Drawable to be deleted from the queue on the next compaction.
	void free(DrawableT<T> & Drawable)
	{
		Drawable.mIsDeleted = true;
		mNeedsCompact = true;
	}

	/// \brief Compact the array, removing all deleted allocations.
	void compact()
	{
		std::size_t Index = 0;
		for (auto & Drawable : mDrawables) {
			if (Drawable->mIsDeleted) continue;
			mDrawables[Index] = Drawable;
			++Index;
		}
		mDrawables.resize(Index);
	}

	/// \brief Mark a Drawable as needing to be redrawn.
	void markNeedsRedraw(DrawableT<T> & Drawable)
	{
		// Right now we redraw the entire queue when something needs to be redrawn.
		mNeedsRedraw = true;
	}

	/// \brief Grow the array if needed and draw all allocations, then upload.
	void upload()
	{
		// Mapping a buffer of size 0 will signal an OpenGL error.
		if (mSize == 0) return;

		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		// If the buffer is too small, resize it
		if (mSize > mCapacity) {
			if (mCapacity == 0) mCapacity = 1;
			while (mSize > mCapacity) mCapacity *= 2;
			glBufferData(GL_ARRAY_BUFFER, mCapacity * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
		}

		// Map the buffer and draw all allocations, then unmap
		// Use the invalidate flag so we dont block
		auto Flags = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		auto BufferPointer = glMapBufferRange(GL_ARRAY_BUFFER, 0, mSize * sizeof(T), Flags);
		auto VertexPointer = static_cast<T *>(BufferPointer);

		for (auto & Drawable : mDrawables) {
			Drawable->draw(VertexPointer);
			VertexPointer += Drawable->mSize;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/// \brief Compact the array if needed, upload the array if needed.
	void update()
	{
		if (mNeedsCompact) {
			compact();
			mNeedsCompact = false;
		}
		if (mNeedsRedraw) {
			upload();
			mNeedsRedraw = false;
		}
	}

	/// \returns The number of vertices in the queue.
	std::size_t getSize() const
	{
		return mSize;
	}
};

}
}
