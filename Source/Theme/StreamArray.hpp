#pragma once

#include "Drawable.hpp"
#include "Settings.hpp"
#include "Gl/Buffer.hpp"
#include "Gl/Context.hpp"
#include "Gl/VertexArray.hpp"

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
	private:
	static std::size_t const mNumBuffers = Settings::Manager::NumBuffers;
	Gl::BufferT mBuffers[mNumBuffers];
	Gl::VertexArrayT mArray[mNumBuffers];
	std::size_t mCapacity[mNumBuffers] = {};
	std::size_t mSize = 0;
	std::size_t mIndex = 0;
	std::vector<DrawableT<T> *> mDrawables;

	std::size_t mDrawCycles = 0;
	bool mNeedsResize = false;

	// Non copyable
	StreamArrayT(StreamArrayT &) = delete;
	StreamArrayT & operator=(StreamArrayT &) = delete;

	public:
	StreamArrayT()
	{
		// Setup all VertexArray's in our ring buffer.
		for (std::size_t Index = 0; Index != mNumBuffers; ++Index) {
			glBindVertexArray(mArray[Index]);
			glBindBuffer(GL_ARRAY_BUFFER, mBuffers[Index]);
			T::setup();
			glBindVertexArray(0);
		}
	}

	/// \returns The VertexArray for the specified index.
	Gl::VertexArrayT & getVertexArray(std::size_t Index)
	{
		return mArray[Index];
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

		// Perform an in place boolean sort. This moves all resized allocations to the end of the
		// array. Anything after the first resized allocation must have its index updated and be
		// redrawn. The sort is stable for the non-resized allocations but unstable for the resized.
		// Over time the static allocations will end up at the start of the array and never need
		// to be redrawn.

		// Find the first allocation to be resized
		std::size_t TrueIndex = 0;
		while (!mDrawables[TrueIndex]->mNeedsResize) ++TrueIndex;
		std::size_t FalseIndex = TrueIndex + 1;
		std::size_t VertexIndex = mDrawables[TrueIndex]->mIndex;
		std::size_t Size = mDrawables.size();

		// Move all resized allocations to the end and update the non-resized indices.
		while (FalseIndex < Size) {
			if (!mDrawables[FalseIndex]->mNeedsResize) {
				mDrawables[FalseIndex]->mIndex = VertexIndex;
				mDrawables[FalseIndex]->mDrawCycles = mNumBuffers;
				VertexIndex += mDrawables[FalseIndex]->mSize;
				std::swap(mDrawables[TrueIndex], mDrawables[FalseIndex]);
				++TrueIndex;
			}
			++FalseIndex;
		}

		// Update the resized indices.
		while (TrueIndex < Size) {
			mDrawables[TrueIndex]->mIndex = VertexIndex;
			mDrawables[TrueIndex]->mNeedsResize = false;
			mDrawables[TrueIndex]->mDrawCycles = mNumBuffers;
			VertexIndex += mDrawables[TrueIndex]->mSize;
			++TrueIndex;
		}

		mSize = VertexIndex;
	}

	/// \brief Grow the array if needed and draw all allocations, then upload.
	void upload(std::size_t Index)
	{
		if (mDrawCycles == 0) return;
		--mDrawCycles;

		// Mapping a buffer of size 0 will signal an OpenGL error.
		if (mSize == 0) return;

		// Select the correct buffer for this frame
		auto & Buffer = mBuffers[Index];
		auto & Capacity = mCapacity[Index];

		glBindBuffer(GL_ARRAY_BUFFER, Buffer);

		// If the buffer is too small, resize it
		if (mSize > Capacity) {
			if (Capacity == 0) Capacity = 1;
			while (mSize > Capacity) Capacity *= 2;
			glBufferData(GL_ARRAY_BUFFER, Capacity * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
		}

		// Map the buffer and draw all allocations, then unmap. We use a ring buffer to avoid
		// synchronization. The caller needs to use a fence just in case.
		auto Flags = GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
		auto BufferPointer = glMapBufferRange(GL_ARRAY_BUFFER, 0, mSize * sizeof(T), Flags);
		auto VertexPointer = static_cast<T *>(BufferPointer);

		// Draw all needed allocations
		for (auto Drawable : mDrawables) {
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
