#pragma once

#include "Drawable.hpp"
#include "Settings.hpp"
#include "Gl/Buffer.hpp"
#include "Gl/Context.hpp"
#include "Gl/VertexArray.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace Twil {
namespace Theme {

/// \brief Container for a dynamically growing OpenGL buffer for streaming data into.
///
/// \param T The vertex type.
template<typename T>
class StreamArrayT
{
	StreamArrayT(StreamArrayT const &) = delete;
	StreamArrayT & operator =(StreamArrayT const &) = delete;

	private:
	static std::size_t const mNumBuffers = Settings::Manager::NumBuffers;
	Gl::BufferT mBuffer;
	Gl::VertexArrayT mArray;
	std::size_t mCapacity = 0;
	std::size_t mSize = 0;
	std::size_t mIndex = 0;
	std::vector<DrawableT<T> *> mDrawables;

	std::size_t mDrawCycles = 0;
	bool mNeedsResize = false;

	public:
	StreamArrayT()
	{
		glBindVertexArray(mArray);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
		T::setup();
		glBindVertexArray(0);
	}

	/// \returns The VertexArray for the specified index.
	Gl::VertexArrayT & getVertexArray()
	{
		return mArray;
	}

	// \returns The VertexArray for the specified index.
	GLuint getVertexIndex(std::size_t Index)
	{
		return mCapacity * Index;
	}

	/// \brief Allocate space for a Drawable.
	void allocate(DrawableT<T> & Drawable, std::size_t Size)
	{
		Drawable.mSize = Size;
		Drawable.mIndex = mSize;
		Drawable.mDrawCycles = mNumBuffers;
		mDrawables.push_back(&Drawable);
		mSize += Size;
		mDrawCycles = true;
	}

	/// \brief Mark an allocation for resizing.
	void resize(DrawableT<T> & Drawable, std::size_t Size)
	{
		Drawable.mSize = Size;
		Drawable.mNeedsResize = true;
		mNeedsResize = true;
	}

	/// \brief Mark a Drawable for drawing.
	void markNeedsRedraw(DrawableT<T> & Drawable)
	{
		Drawable.mDrawCycles = mNumBuffers;
		mDrawCycles = mNumBuffers;
	}

	/// \brief Perform all pending resizes.
	void resize()
	{
		if (!mNeedsResize) return;
		mNeedsResize = false;

		// Move all resized allocations to the end of the array. Anything after the first resized
		// allocation must have its index updated and be redrawn. Over time the static allocations
		// will end up at the start of the array and never need to be redrawn.

		auto First = mDrawables.begin();
		auto Last = mDrawables.end();

		auto PartitionFirst = std::find_if(First, Last, [](DrawableT<T> * Drawable)
		{
			return Drawable->mNeedsResize;
		});

		assert(PartitionFirst != Last);
		std::size_t VertexIndex = (*PartitionFirst)->mIndex;

		std::partition(PartitionFirst, Last, [](DrawableT<T> * Drawable)
		{
			return !Drawable->mNeedsResize;
		});

		std::for_each(PartitionFirst, Last, [&](DrawableT<T> * Drawable)
		{
			Drawable->mIndex = VertexIndex;
			Drawable->mNeedsResize = false;
			Drawable->mDrawCycles = mNumBuffers;
			VertexIndex += Drawable->mSize;
		});

		mSize = VertexIndex;
	}

	/// \brief Grow the array if needed and draw all allocations, then upload.
	void upload(std::size_t Index)
	{
		if (mDrawCycles == 0) return;
		--mDrawCycles;

		// Mapping a buffer of size 0 will signal an OpenGL error.
		if (mSize == 0) return;

		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		// If the buffer is too small, resize it
		if (mSize > mCapacity)
		{
			if (mCapacity == 0) mCapacity = 1;
			while (mSize > mCapacity) mCapacity *= 2;
			glBufferData(
				GL_ARRAY_BUFFER,
				mCapacity * mNumBuffers * sizeof(T),
				nullptr,
				GL_DYNAMIC_DRAW);

			// Everything needs to be redrawn on a resize
			mDrawCycles = mNumBuffers;
			for (auto Drawable : mDrawables) Drawable->mDrawCycles = mNumBuffers;
		}

		// Map the buffer and draw all allocations, then unmap. We use a ring buffer to avoid
		// synchronization. The caller needs to use a fence just in case.
		auto VertexPointer = static_cast<T *>(
			glMapBufferRange(
				GL_ARRAY_BUFFER,
				getVertexIndex(Index) * sizeof(T),
				mSize * sizeof(T),
				GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT));

		// Draw all needed allocations
		for (auto Drawable : mDrawables)
		{
			if (Drawable->mDrawCycles == 0) continue;
			Drawable->draw(VertexPointer + Drawable->mIndex);
			--Drawable->mDrawCycles;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, 0);	
	}

	bool checkNeedsRedraw()
	{
		return mDrawCycles == mNumBuffers;
	}

	/// \brief Compact the array if needed, upload the array if needed.
	void update(std::size_t Index)
	{
		resize();
		upload(Index);
	}

	/// \returns The number of vertices in the queue.
	std::size_t getSize() const
	{
		return mSize;
	}
};

}
}
