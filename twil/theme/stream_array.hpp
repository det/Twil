#pragma once

#include "stream_array.hxx"

#include "drawable.hpp"
#include "settings.hpp"
#include "gl/buffer.hpp"
#include "gl/context.hpp"
#include "gl/vertex_array.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace twil {
namespace theme {

/// \brief Container for a dynamically growing OpenGL buffer for streaming data into.
///
/// \param T The vertex type.
template<typename T>
class StreamArray
{
	StreamArray(StreamArray const &) = delete;
	StreamArray & operator =(StreamArray const &) = delete;

private:
	static std::size_t const num_buffers_ = settings::manager::num_buffers;

	gl::Buffer buffer_;
	gl::VertexArray array_;
	std::size_t capacity_ = 0;
	std::size_t sizes_[num_buffers_] = {};
	std::vector<Drawable<T> *> drawables_;

	std::size_t draw_cycles_ = 0;
	bool needs_resize_ = false;

public:
	StreamArray()
	{
		glBindVertexArray(array_);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_);
		T::Setup();
		glBindVertexArray(0);
	}

	/// \brief Allocate space for a Drawable.
	void Allocate(Drawable<T> & drawable, std::size_t size)
	{
		drawable.size_ = size;
		drawable.draw_cycles_ = num_buffers_;
		drawables_.push_back(&drawable);
		draw_cycles_ = true;
	}

	/// \brief Mark an allocation for resizing.
	void Resize(Drawable<T> & drawable, std::size_t size)
	{
		drawable.size_ = size;
		drawable.needs_resize_ = true;
		needs_resize_ = true;
	}

	/// \brief Mark a Drawable for drawing.
	void MarkNeedsRedraw(Drawable<T> & drawable)
	{
		drawable.draw_cycles_ = num_buffers_;
		draw_cycles_ = num_buffers_;
	}

	/// \brief Perform all pending resizes.
	void Resize()
	{
		if (!needs_resize_) return;
		needs_resize_ = false;

		// Move all resized allocations to the end of the array. Anything after the first resized
		// allocation must have its index updated and be redrawn. Over time the static allocations
		// will end up at the start of the array and never need to be redrawn.

		auto first = drawables_.begin();
		auto last = drawables_.end();

		auto partition_first = std::find_if(first, last, [](Drawable<T> * drawable)
		{
			return drawable->needs_resize_;
		});

		std::partition(partition_first, last, [](Drawable<T> * drawable)
		{
			return !drawable->needs_resize_;
		});

		std::for_each(partition_first, last, [&](Drawable<T> * drawable)
		{
			drawable->needs_resize_ = false;
			drawable->draw_cycles_ = num_buffers_;
		});
	}

	/// \brief Grow the array if needed and draw all allocations, then upload.
	void Upload(std::size_t index)
	{
		if (draw_cycles_ == 0) return;

		glBindBuffer(GL_ARRAY_BUFFER, buffer_);

		// Calculate the size of the buffer.
		sizes_[index] = 0;
		for (auto drawable : drawables_) sizes_[index] += drawable->size_;

		// Mapping a buffer of size 0 will signal an OpenGL error.
		if (sizes_[index] == 0) return;

		// If the buffer is too small, resize it
		if (sizes_[index] > capacity_)
		{
			if (capacity_ == 0) capacity_ = 1;
			while (sizes_[index] > capacity_) capacity_ = capacity_ * 3 / 2 + 1;
			glBufferData(
				GL_ARRAY_BUFFER,
				capacity_ * num_buffers_ * sizeof(T),
				nullptr,
				GL_DYNAMIC_DRAW);

			// Everything needs to be redrawn on a resize
			draw_cycles_ = num_buffers_;
			for (auto drawable : drawables_) drawable->draw_cycles_ = num_buffers_;
		}

		// Map the buffer and draw all allocations, then unmap. We use a ring buffer to avoid
		// synchronization. The caller needs to use a fence just in case.
		auto vertex_pointer = static_cast<T *>(
			glMapBufferRange(
				GL_ARRAY_BUFFER,
				GetVertexIndex(index) * sizeof(T),
				sizes_[index] * sizeof(T),
				GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT));

		// Draw all needed allocations
		for (auto drawable : drawables_)
		{
			if (drawable->draw_cycles_ != 0)
			{
				drawable->Draw(vertex_pointer);
				--drawable->draw_cycles_;
			}
			vertex_pointer += drawable->size_;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		--draw_cycles_;
	}

	bool CheckNeedsRedraw()
	{
		return draw_cycles_ == num_buffers_;
	}

	/// \brief Compact the array if needed, upload the array if needed.
	void Update(std::size_t index)
	{
		Resize();
		Upload(index);
	}

	/// \returns The number of vertices in the queue.
	std::size_t GetSize(std::size_t index) const
	{
		return sizes_[index];
	}

	/// \returns The VertexArray for the specified index.
	gl::VertexArray & GetVertexArray(std::size_t index)
	{
		return array_;
	}

	/// \returns The Vertex Index for the specified index.
	// \returns The VertexArray for the specified index.
	std::uint32_t GetVertexIndex(std::size_t index)
	{
		return capacity_ * index;
	}

	void draw(std::size_t index)
	{
		glBindVertexArray(GetVertexArray(index));
		glDrawArrays(GL_POINTS,	GetVertexIndex(index), GetSize(index));
		glBindVertexArray(0);
	}
};

}
}
