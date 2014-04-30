#pragma once

#include "BitmapFwd.hpp"

#include "LibraryFwd.hpp"
#include "OutlineFwd.hpp"
#include "FaceFwd.hpp"

#include <cstdint>
#include <iterator>
#include <utility>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H

namespace Twil {
namespace Ft {

/// \brief An iterator that operates on a sub rectangle of a Twil::Ft::BitmapT.
class SubBitmapIteratorT
:
	public std::iterator<std::input_iterator_tag, std::uint8_t>
{
	friend class BitmapT;

private:
	std::uint8_t const * mPointer;
	std::size_t mPitch;
	std::size_t mWidth;
	std::size_t mRowCount;

	SubBitmapIteratorT(
		std::uint8_t const * Pointer,
		std::size_t Pitch,
		std::size_t Width,
		std::size_t RowCount);

public:
	SubBitmapIteratorT & operator++();
	bool operator==(SubBitmapIteratorT const &);
	bool operator!=(SubBitmapIteratorT const &);
	std::uint8_t operator*() const;
};

/// \brief An 8 bit FreeType bitmap used as a target for rendering operations.
class BitmapT
{
	BitmapT(BitmapT const &) = delete;
	BitmapT & operator =(BitmapT const &) = delete;

private:
	LibraryT * mLibrary;
	FT_Bitmap mId;
	std::size_t mCapacity;

public:
	using RangeT = std::pair<SubBitmapIteratorT, SubBitmapIteratorT>;

	/// \brief Construct a 0 size bitmap.
	BitmapT(LibraryT & Library);

	~BitmapT() noexcept;

	/// \returns The width in bytes;
	int getWidth() const;

	/// \returns The height in bytes;
	int getRows() const;

	/// \brief Resize to the specified size and initialize all bytes to 0.
	void resize(std::size_t Width, std::size_t Height);

	/// \brief Render an outline.
	///
	/// Behaviour is undefined if the outline is outside the bitmap.
	void render(OutlineT & Outline);

	/// \brief Render a face.
	///
	/// Behaviour is undefined if the face is outside the bitmap.
	void render(FaceT & Face);

	/// \returns The size of the bitmap in bytes.
	std::size_t size() const;

	/// \returns A pointer to the first byte of the bitmap, or nullptr if it is size 0.
	std::uint8_t const * data() const;

	/// \returns The begin iterator for the bytes of the bitmap.
	std::uint8_t const * begin() const;

	/// \returns The end iterator for the bytes of the bitmap.
	std::uint8_t const * end() const;

	/// \returns A pair of begin and end iterators for the bytes of a sub-rectangle of the bitmap.
	RangeT getSubRange(std::size_t X, std::size_t Y, std::size_t Width, std::size_t Height);
};

}
}
