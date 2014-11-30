#pragma once

#include "bitmap.hxx"

#include "library.hxx"
#include "outline.hxx"
#include "face.hxx"

#include <cstdint>
#include <iterator>
#include <utility>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H

namespace twil {
namespace ft {

/// \brief An iterator that operates on a sub rectangle of a twil::Ft::Bitmap.
class SubBitmapIterator
:
	public std::iterator<std::input_iterator_tag, std::uint8_t>
{
	friend Bitmap;

private:
	std::uint8_t const * pointer_;
	std::size_t pitch_;
	std::size_t width_;
	std::size_t row_count_;

	SubBitmapIterator(
		std::uint8_t const * pointer,
		std::size_t pitch,
		std::size_t width,
		std::size_t row_count);

public:
	SubBitmapIterator & operator++();
	bool operator==(SubBitmapIterator const &);
	bool operator!=(SubBitmapIterator const &);
	std::uint8_t operator*() const;
};

/// \brief An 8 bit FreeType bitmap used as a target for rendering operations.
class Bitmap
{
	Bitmap(Bitmap const &) = delete;
	Bitmap & operator =(Bitmap const &) = delete;

private:
	Library * library_;
	FT_Bitmap id_;
	std::size_t capacity_;

public:
	using Range = std::pair<SubBitmapIterator, SubBitmapIterator>;

	/// \brief Construct a 0 size bitmap.
	Bitmap(Library & library);

	~Bitmap() noexcept;

	/// \returns The width in bytes;
	int GetWidth() const;

	/// \returns The height in bytes;
	int GetRows() const;

	/// \brief Resize to the specified size and initialize all bytes to 0.
	void Resize(std::size_t width, std::size_t height);

	/// \brief Render an outline.
	///
	/// Behaviour is undefined if the outline is outside the bitmap.
	void Render(Outline & outline);

	/// \brief Render a face.
	///
	/// Behaviour is undefined if the face is outside the bitmap.
	void Render(Face & face);

	/// \returns The size of the bitmap in bytes.
	std::size_t size() const;

	/// \returns A pointer to the first byte of the bitmap, or nullptr if it is size 0.
	std::uint8_t const * data() const;

	/// \returns The begin iterator for the bytes of the bitmap.
	std::uint8_t const * begin() const;

	/// \returns The end iterator for the bytes of the bitmap.
	std::uint8_t const * end() const;

	/// \returns A pair of begin and end iterators for the bytes of a sub-rectangle of the bitmap.
	Range GetSubRange(std::size_t x, std::size_t y, std::size_t width, std::size_t height);
};

}
}
