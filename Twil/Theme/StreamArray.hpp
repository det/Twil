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
	std::size_t mSizes[mNumBuffers] = {};
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

	/// \brief Allocate space for a Drawable.
	void allocate(DrawableT<T> & Drawable, std::size_t Size)
	{
		Drawable.mSize = Size;
		Drawable.mDrawCycles = mNumBuffers;
		mDrawables.push_back(&Drawable);
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

		std::partition(PartitionFirst, Last, [](DrawableT<T> * Drawable)
		{
			return !Drawable->mNeedsResize;
		});

		std::for_each(PartitionFirst, Last, [&](DrawableT<T> * Drawable)
		{
			Drawable->mNeedsResize = false;
			Drawable->mDrawCycles = mNumBuffers;
		});
	}

	/// \brief Grow the array if needed and draw all allocations, then upload.
	void upload(std::size_t Index)
	{
		if (mDrawCycles == 0) return;		

		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		// Calculate the size of the buffer.
		mSizes[Index] = 0;
		for (auto Drawable : mDrawables) mSizes[Index] += Drawable->mSize;

		// Mapping a buffer of size 0 will signal an OpenGL error.
		if (mSizes[Index] == 0) return;

		// If the buffer is too small, resize it
		if (mSizes[Index] > mCapacity)
		{
			if (mCapacity == 0) mCapacity = 1;
			while (mSizes[Index] > mCapacity) mCapacity *= 2;
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
				mSizes[Index] * sizeof(T),
				GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT));

		// Draw all needed allocations
		for (auto Drawable : mDrawables)
		{
			if (Drawable->mDrawCycles != 0)
			{
				Drawable->draw(VertexPointer);
				--Drawable->mDrawCycles;
			}
			VertexPointer += Drawable->mSize;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		--mDrawCycles;
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
	std::size_t getSize(std::size_t Index) const
	{
		return mSizes[Index];
	}

	/// \returns The VertexArray for the specified index.
	Gl::VertexArrayT & getVertexArray(std::size_t Index)
	{
		return mArray;
	}

	/// \returns The Vertex Index for the specified index.
	// \returns The VertexArray for the specified index.
	GLuint getVertexIndex(std::size_t Index)
	{
		return mCapacity * Index;
	}

	void draw(std::size_t Index)
	{
		glBindVertexArray(getVertexArray(Index));
		glDrawArrays(GL_POINTS,	getVertexIndex(Index), getSize(Index));
		glBindVertexArray(0);
	}
};

}
}
